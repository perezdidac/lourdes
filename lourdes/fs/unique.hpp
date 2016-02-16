#ifndef __LOURDES_FS_UNIQUE_HPP
#define __LOURDES_FS_UNIQUE_HPP

/// \example    examples/fs/unique.cpp
namespace lourdes { namespace fs {

/// \brief  Creates a temporal file name.
/// \param  filename    A pointer to a string which will contain the generated
/// file name. The allocated memory must be at least 256 bytes.
void unique(char* filename);

}}

#endif // __LOURDES_FS_UNIQUE_HPP
