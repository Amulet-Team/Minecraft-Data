# BedrockData

This is a project to extract data from the Bedrock server.

It works by injecting a .dll file into the running server to call functions in the server itself.

It uses LiteLoaderBDS but due to the need to run on past versions of the server it cannot use the APIs that are added on top.

Due to this it is more difficult that just creating a plugin for LiteLoaderBDS.

## Download

Clone the repository and dependencies using the following command. It will download it in the working directory.

`git clone --recurse-submodules -j8 https://github.com/Amulet-Team/Minecraft-Data`

## Run

1) Download the Bedrock Dedicated Server.
2) Unzip everything into a directory of your choice. This directory will be referred to as `<server_dir>`
3) Make sure that `bedrock_server.pdb` exists because it is required later.
4) Copy `LLPreLoader.dll` from `LLPreLoader` to `<server_dir>`
5) Copy `LLPeEditor.exe` from `LiteLoaderSDK\Tools` to `<server_dir>`
6) Run `LLPeEditor.exe` in `<server_dir>` which will create `bedrock_server_mod.exe`
7) Run `generate_lib.bat <server_dir>` where `<server_dir>` is the directory `bedrock_server.exe` is in. This generates `.lib` files in `Lib` from the `bedrock_server.pdb` which are used to compile the code.
8) Open BedrockData.sln (requires Visual Studio)
9) Right click the solution in Solution Explorer and click `Build Solution`
10) Copy `BedrockData.dll` from `x64/Release` to `<server_dir>/plugins`
11) Run `bedrock_server_mod.exe`. The server will start and close a short while after.
12) In `<server_dir>` there will be a new directory called `generated` within which will be the output files.

## Development
When developing the code you can set the working directory to the server directory.

Right click BedrockData project -> Properties -> Configuration Properties -> Debugging -> Working Directory (set to server directory)

Doing this will copy the built dll to the server plugins directory and run the server when you run the debugger after it has built.

## TODO
- write a script to automate the above steps
- Work out how to compile headers for each version

## Acknowledgements

I would like to thank the LiteLoaderBDS developers for developing this tool and for helping me make it work with old versions.

## Links
LiteLoaderBDS - https://github.com/LiteLDev/LiteLoaderBDS

Developer discussion  - https://github.com/LiteLDev/LiteLoaderBDS/discussions/795
