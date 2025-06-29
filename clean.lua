-- This script that can be called with ./premake5 clean, cleans up the build generations of the project
-- useful for non-evolutive integrations or solving new integrations that doesnt get compiled
newaction {
    trigger     = "clean",
    description = "clean the generated gmake files",
    execute     = function ()
       print("clean the build...")
       os.rmdir("./bin")
       os.rmdir("./bin-int")
       os.rmdir("./obj")
       os.remove("./Makefile")
       os.remove("./*.make")
       -- Remove windows Visual Studio files:
       -- os.remove("./*.sln")
       -- os.remove("./*.vcxproj")
       -- os.remove("./*.vcxproj.filters")
       -- os.remove("./*.vcxproj.user")
       print("done.")
    end
 }