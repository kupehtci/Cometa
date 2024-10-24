newaction {
    trigger     = "clean",
    description = "clean the generated gmake files",
    execute     = function ()
       print("clean the build...")
       os.rmdir("./bin")
       os.rmdir("./obj")
       os.remove("./Makefile")
       os.remove("./*.make")
       print("done.")
    end
 }