// OgreBatchConverter.cpp : Defines the entry point for the console application.
//

#include <Urho3D/Core/Context.h>
#include <Urho3D/Core/ProcessUtils.h>
#include <Urho3D/IO/FileSystem.h>

using namespace Urho3D;

Context* GetContext() {
    static SharedPtr<Context> context_(new Context());
    return context_;
}

FileSystem* GetFileSystem() {
    static SharedPtr<FileSystem> fileSystem_(new FileSystem(GetContext()));
    return fileSystem_;
}

int main(int argc, char** argv)
{
    // Take in account args and place on OgreImporter args
    const Vector<String>& args = ParseArguments(argc, argv);
    Vector<String> files;
    String currentDir = GetFileSystem()->GetCurrentDir();

    // Try to execute OgreImporter from same directory as this executable
    String ogreImporterName = GetFileSystem()->GetProgramDir() + "OgreImporter";

    printf("\n\nOgreBatchConverter requires OgreImporter.exe on same directory");
    printf("\nSearching Ogre file in Xml format in %s\n" ,currentDir.CString());
    GetFileSystem()->ScanDir(files, currentDir, "*.xml", SCAN_FILES, true);
    printf("\nFound %d files\n", files.Size());
    #ifdef WIN32
    if (files.Size()) GetFileSystem()->SystemCommand("pause");
    #endif

    for (unsigned i = 0 ; i < files.Size(); i++)
    {
        Vector<String> cmdArgs;
        cmdArgs.Push(files[i]);
        cmdArgs.Push(ReplaceExtension(files[i], ".mdl"));
        cmdArgs.Push(args);

        String cmdPreview = ogreImporterName;
        for (unsigned j = 0; j < cmdArgs.Size(); j++)
            cmdPreview += " " + cmdArgs[j];

        printf("\n%s", cmdPreview.CString());
        GetFileSystem()->SystemRun(ogreImporterName, cmdArgs);
    }

    printf("\nExit\n");
    #ifdef WIN32
    GetFileSystem()->SystemCommand("pause");
    #endif

    return 0;
}

