#ifndef __LOURDES_FS_FILE_HPP
#define __LOURDES_FS_FILE_HPP

/// \example    examples/fs/file.cpp
namespace lourdes { namespace fs {

class FileImpl;

/// \brief  Represents a file.
class File
{
public:
    typedef enum
    {
        OPEN_MODE_READ,
        OPEN_MODE_WRITE,
    } OpenMode;
public:
    /// \brief  Initializes the object and all the associated resources to it.
    File();

    /// \brief  Destroys the object and all the associated resources to it.
    ~File();

    /// \brief  Tries to open the file.
    /// \param  filename    File name of the file to be open.
    /// \param  openMode    Specifies the open mode.
    /// \return A flag which indicates if the file has been open.
    bool open(const char* filename, OpenMode openMode);

    /// \brief  Reads data from the file.
    /// \param  buffer  A pointer in which put the data.
    /// \param  length  Total length of the data to be read.
    /// \return A flag which indicates if the operation has succeed.
    bool read(char* buffer, int length);

    /// \brief  Writes data to the file.
    /// \param  buffer  A pointer to the data to be written.
    /// \param  length  Total length of the data to be written.
    /// \return A flag which indicates if the operation has succeed.
    bool write(const char* buffer, int length);

    /// \brief  Closes the file, if open.
    void close();

private:
    File(File const&);
    File& operator=(File const&);
    FileImpl* impl;
};

}}

#endif // __LOURDES_FS_FILE_HPP
