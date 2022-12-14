from dataclasses import dataclass, field

from jawa.classloader import ClassLoader
from jawa.cf import ClassFile
from jawa.util.bytecode import OperandTypes
from jawa.methods import Method
from jawa.constants import MethodReference, ConstantClass, String, InterfaceMethodRef, FieldReference, InvokeDynamic
from jawa.util.descriptor import method_descriptor


def serialise(obj) -> str:
    if isinstance(obj, (MethodReference, InterfaceMethodRef)):
        return f"Method {obj.class_.name.value}.{obj.name_and_type.name.value}{obj.name_and_type.descriptor.value}"
    elif isinstance(obj, InvokeDynamic):
        return f"Dynamic {obj.name_and_type.name.value}{obj.name_and_type.descriptor.value}"
    elif isinstance(obj, FieldReference):
        return f"Field {obj.class_.name.value}.{obj.name_and_type.name.value} -> {obj.name_and_type.descriptor.value}"
    elif isinstance(obj, ConstantClass):
        return f"Class {obj.name.value}"
    elif isinstance(obj, String):
        return f"String \"{obj.string.value}\""
    else:
        return str(obj)


@dataclass
class JavaPState:
    methods: set[Method] = field(default_factory=set)
    indent: int = 0


@dataclass
class ClassFileInheritance:
    parents: set[str] = field(default_factory=set)
    interfaces: set[str] = field(default_factory=set)


class InheritanceState:
    def __init__(self, loader: ClassLoader):
        self._loader = loader
        self._classes: dict[str, ClassFileInheritance] = {}
        self._subclasses: dict[str, set[str]] = {}
        self._implementations: dict[str, set[str]] = {}
        for class_path in loader.classes:
            self._get_class(class_path)

    def _get_class(self, class_path: str) -> ClassFileInheritance:
        if class_path not in self._classes:
            try:
                cf = self._loader[class_path]
            except FileNotFoundError:
                self._classes[class_path] = data = ClassFileInheritance()
            else:
                superclass = self._get_class(cf.super_.name.value)
                self._classes[class_path] = data = ClassFileInheritance()
                data.parents.add(class_path)
                data.parents.update(superclass.parents)
                data.interfaces.update(class_path)
                data.interfaces.update(map(lambda i: i.name.value, cf.interfaces))
                data.interfaces.update(superclass.interfaces)
            for parent in data.parents:
                self._subclasses.setdefault(parent, set()).add(class_path)
            for interface in data.interfaces:
                self._implementations.setdefault(interface, set()).add(class_path)

        return self._classes[class_path]

    def subclasses(self, base_class_path: str) -> tuple[str]:
        """Get all subclasses of this class."""
        return tuple(self._subclasses.get(base_class_path, ()))

    def implementations(self, interface_path: str) -> tuple[str]:
        """Get all classes that implement this interface."""
        return tuple(self._implementations.get(interface_path, ()))


def javap(loader: ClassLoader, cf: ClassFile, method: Method) -> str:
    return _javap(loader, cf, method, JavaPState(), InheritanceState(loader))


def _javap(loader: ClassLoader, cf: ClassFile, method: Method, state: JavaPState, inheritance: InheritanceState) -> str:
    lines = []

    flags = method.access_flags.to_dict()
    flags = [k for k, v in flags.items() if v]

    lines.append('{}{} {} {}({}) {{'.format(
        "\t" * state.indent,
        ' '.join(flags),
        method.returns.name,
        method.name.value,
        ', '.join(a.name + ('[]' * a.dimensions) for a in method.args)
    ).strip())

    if method in state.methods:
        lines.append("\t" * (state.indent+1) + "Skipping duplicated code.")
    elif method.code:
        state.methods.add(method)
        instructions = list(method.code.disassemble())
        for index, ins in enumerate(instructions):
            mnemomic: str = ins.mnemonic[:-2] if ins.mnemonic.endswith("_w") else ins.mnemonic
            if mnemomic.startswith("aload"):
                mnemomic = "aload"
            elif mnemomic.startswith("astore"):
                mnemomic = "astore"
            line = [f'{mnemomic:<15} <-']

            for operand in ins.operands:
                if isinstance(operand, dict):
                    line.append(f'JT[{operand!r}]')
                elif operand.op_type is OperandTypes.CONSTANT_INDEX:
                    line.append(serialise(cf.constants[operand.value]))
                elif operand.op_type is OperandTypes.BRANCH:
                    byte_distance = operand.value
                    byte_index = byte_distance + ins.pos
                    opcode_index = next(filter(lambda i: instructions[i].pos == byte_index, range(len(instructions))), None)
                    if opcode_index is None:
                        raise RuntimeError(f"Could not find instruction at offset {byte_distance}")
                    line.append(f'J[{opcode_index - index}]')
                elif operand.op_type is OperandTypes.LITERAL:
                    line.append(f'#[{operand.value}]')
                elif operand.op_type is OperandTypes.LOCAL_INDEX:
                    line.append(f'L[]')
                elif operand.op_type is OperandTypes.PADDING:
                    pass
                else:
                    raise Exception

            lines.append("\t" * (state.indent+1) + ' '.join(line))

            if mnemomic in {"invokestatic", "invokespecial"}:
                method_ref = cf.constants[ins.operands[0].value]
                class_path = method_ref.class_.name.value
                name_and_type = method_ref.name_and_type
                try:
                    cf2 = loader[class_path]
                except FileNotFoundError:
                    pass
                else:
                    descriptor = method_descriptor(name_and_type.descriptor.value)
                    method2 = cf2.methods.find_one(name=name_and_type.name.value, args=descriptor.args_descriptor, returns=descriptor.returns_descriptor)
                    if method2 is not None:
                        state.indent += 2
                        lines.append("\t" * state.indent + _javap(loader, cf2, method2, state, inheritance))
                        state.indent -= 2
                    else:
                        print("hi")
            elif mnemomic == "invokeinterface":
                # Find the method for each subclass
                method_ref = cf.constants[ins.operands[0].value]
                name_and_type = method_ref.name_and_type
                descriptor = method_descriptor(name_and_type.descriptor.value)
                for class_path in sorted(inheritance.implementations(method_ref.class_.name.value)):
                    cf2 = loader[class_path]
                    method2 = cf2.methods.find_one(name=name_and_type.name.value, args=descriptor.args_descriptor, returns=descriptor.returns_descriptor)
                    if method2 is not None:
                        state.indent += 2
                        lines.append("\t" * state.indent + class_path)
                        lines.append("\t" * state.indent + _javap(loader, cf2, method2, state, inheritance))
                        state.indent -= 2
            elif mnemomic == "invokevirtual":
                # Find the method for each subclass
                method_ref = cf.constants[ins.operands[0].value]
                name_and_type = method_ref.name_and_type
                descriptor = method_descriptor(name_and_type.descriptor.value)
                # Find all classes that subclass the class that defines the virtual method
                for class_path in sorted(inheritance.subclasses(method_ref.class_.name.value)):
                    cf2 = loader[class_path]
                    method2 = cf2.methods.find_one(name=name_and_type.name.value, args=descriptor.args_descriptor, returns=descriptor.returns_descriptor)
                    if method2 is not None:
                        state.indent += 2
                        lines.append("\t" * state.indent + class_path)
                        lines.append("\t" * state.indent + _javap(loader, cf2, method2, state, inheritance))
                        state.indent -= 2

    lines.append("\t" * state.indent + '}')

    return "\n".join(lines)
