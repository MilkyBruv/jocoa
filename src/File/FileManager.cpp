#include "./FileManager.hpp"
#include "./../Utils/Utils.hpp"
#include "./../Log/Logger.hpp"
#include "FileManager.hpp"

string FileManager::newPath;
string FileManager::currentPath;

void FileManager::setCurrentPath()
{
    // Get current path and STANDARDISE it
    currentPath = fs::current_path().string();
    standardisePath(currentPath);
    Logger::info("Current path " + currentPath);
}

void FileManager::createDirectory(string path)
{
    // Get list of all folders
    vector<string> folders = Utils::split(path, "/");
    string currentFolder = currentPath;

    // Can only create each folder at a time so loop through to create them all
    for (const string& folder : folders)
    {
        currentFolder += "/" + folder;

        // Only create if folder doesn't exist
        if (!fs::is_directory(currentFolder))
        {
            // Try create directory
            if (fs::create_directory(currentFolder))
            {
                Logger::info("Created " + currentFolder);
            }
            else
            {
                Logger::error("Failed to create " + currentFolder + " as it already exists");
            }
        }
    }
}

void FileManager::clearDirectory(string path)
{
    // Check if path is a folder
    if (fs::is_directory(currentPath + "/" + path))
    {
        // Loop through all files and folders in path and delete them
        for (const fs::path file : fs::directory_iterator(currentPath + "/bin"))
        {
            fs::remove_all(file);
            Logger::info("Removed " + simplifyPathNew(file.string()));
        }
    }
}

void FileManager::createFile(string path)
{
    // Create file if it doesn't exist
    if (!fs::is_regular_file(currentPath + "/" + path))
    {
        std::ofstream file(currentPath + "/" + path);
        Logger::info("Created " + simplifyPathNew(path));
    }
}

void FileManager::writeFile(string path, string contents)
{
    // Create file if it doesn't exist and clear it
    createFile(path);
    clearFile(path);

    // Write contents to file
    std::ofstream file(currentPath + "/" + path);
    file << contents;
    file.close();

    Logger::info("Wrote to " + simplifyPathNew(currentPath + "/" + path));
}

void FileManager::clearFile(string path)
{
    // Resize file to 0 to clear/truncate it
    std::ofstream file(currentPath + "/" + path);
    fs::resize_file(currentPath + "/" + path, 0);
    file.close();

    Logger::info("Cleared " + simplifyPathNew(currentPath + "/" + path));
}

void FileManager::standardisePath(string& path)
{
    // Windows path delimiters ("\\" and "\")
    string delimiters[] = {"\\\\", "\\"};

    // Loop through each delimiter, and replace all occurences with standard "/"
    for (const auto& delimiter : delimiters)
    {
        size_t i = 0;
        while ((i = path.find(delimiter, i)) != string::npos)
        {
            path.replace(i, delimiter.length(), "/");
            i++;
        }
    }
}

bool FileManager::fileExists(string path)
{
    return fs::is_regular_file(currentPath + "/" + path);
}

void FileManager::localisePath(string& path)
{
    // Replace currentPath with "."
    path.replace(0, currentPath.length(), ".");
}

void FileManager::simplifyPath(string& path)
{
    // Standardise and localise path
    standardisePath(path);
    localisePath(path);
}

string FileManager::simplifyPathNew(string& path)
{
    // New path to return rather than just edit
    newPath = path;

    // Standardise and localise path
    standardisePath(newPath);
    localisePath(newPath);

    return path;
}

void FileManager::searchForFiles(string path, string filetype, vector<string>& jsonArray)
{
    string currentFile;

    Logger::info("Searching " + simplifyPathNew(currentPath + "/" + path));

    // Search {path} and check for files with the type of {filetype}, then add them to {jsonArray}
    for (const fs::directory_entry& file : fs::recursive_directory_iterator(currentPath + "/" + path))
    {   
        if (file.path().extension() == filetype)
        {
            currentFile = file.path().string();
            simplifyPath(currentFile);
            jsonArray.push_back(currentFile);
            Logger::info("Found " + currentFile);
        }
    }
}

string FileManager::getSystemUser()
{
    string user;

    // Get system user name
    #if defined(_WIN32) || defined(_WIN64)
        wchar_t userBuffer[UNLEN + 1];
        DWORD userLen = UNLEN + 1;
        GetUserNameW(userBuffer, &userLen);
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        user = converter.to_bytes(userBuffer);
    #elif defined(__linux__) || defined(_APPLE__) || defined(__unix__)
        char userBuffer[512];
        getlogin_r(userBuffer, 512);
        user = userBuffer;
    #endif

    Logger::info("System user " + user);

    return user;
}
