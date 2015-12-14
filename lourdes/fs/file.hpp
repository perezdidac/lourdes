#ifndef __LOURDES_FS_FILE_HPP
#define __LOURDES_FS_FILE_HPP

/// \example    examples/fs/file.cpp
namespace lourdes { namespace fs {

class FileImpl;

/// \brief  Represents a file.
class File
{
public:
    /// \brief  Initializes the object and all the associated resources to it.
    File();

    /// \brief  Destroys the object and all the associated resources to it.
    ~File();

private:
    File(File const&);
    File& operator=(File const&);
    FileImpl* impl;
};

}}

#endif // __LOURDES_FS_FILE_HPP
