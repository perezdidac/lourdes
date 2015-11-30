#ifndef __LOURDES_CHRONO_DATETIME_HPP
#define __LOURDES_CHRONO_DATETIME_HPP

namespace lourdes { namespace chrono {

/// \brief  Returns the current local date and time with the given format. See
/// http://www.boost.org/doc/libs/1_59_0/doc/html/date_time/date_time_io.html
/// for more information about how the format can be given.
/// \param  format  The given format used to write the output value.
/// \param  output  A string array in which the output will be written.
void local(const char* format, char* output);

/// \brief  Returns the current UTC date and time with the given format. See
/// http://www.boost.org/doc/libs/1_59_0/doc/html/date_time/date_time_io.html
/// for more information about how the format can be given.
/// \param  format  The given format used to write the output value.
/// \param  output  A string array in which the output will be written.
void universal(const char* format, char* output);

}}

#endif // __LOURDES_CHRONO_DATETIME_HPP
