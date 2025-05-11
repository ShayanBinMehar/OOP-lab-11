#include <iostream>
#include <exception>
#include <string>

using namespace std;

class FileException : public exception
{
public:
    FileException(const string &message) : message_(message) {}
    const char *what() const noexcept override
    {
        return message_.c_str();
    }

private:
    string message_;
};

class FileNotFoundException : public FileException
{
public:
    FileNotFoundException(const string &filename)
        : FileException("File not found: " + filename) {}
};

class PermissionDeniedException : public FileException
{
public:
    PermissionDeniedException(const string &filename)
        : FileException("Permission denied: " + filename) {}
};

void readFile(const string &filename)
{

    if (filename == "missing.txt")
    {
        throw FileNotFoundException(filename);
    }
    else if (filename == "secret.txt")
    {
        throw PermissionDeniedException(filename);
    }
    else if (filename == "valid.txt")
    {
        cout << "Successfully read file: " << filename << endl;
    }
    else
    {
        cout << "Successfully read file: " << filename << endl;
    }
}

int main()
{
    try
    {
        readFile("missing.txt");
        readFile("secret.txt");
        readFile("valid.txt");
        readFile("another.txt");
    }
    catch (const FileNotFoundException &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
    catch (const PermissionDeniedException &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
    catch (const FileException &e)
    {
        cerr << "Error (FileException): " << e.what() << endl;
    }

    return 0;
}
