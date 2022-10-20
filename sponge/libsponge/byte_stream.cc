#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity) { 
    _capacity = capacity;
}

size_t ByteStream::write(const string &data) {
    size_t len = data.size();
    if(len > _capacity - write_size) {
        len = _capacity - write_size;
    }
    write_size = write_size + len;
    cache += data.substr(0, len);
    return len;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    string ans;
    size_t n = len;
    if(len > cache.size()) {
        n = cache.size();
    }
    ans = cache.substr(0, n);
    return ans;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) { 
    size_t n = len;
    if(len > cache.size()) {
        n = cache.size();
    }
    read_size += n;
    cache.erase(0, n);
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    string str = peek_output(len);
    pop_output(len);
    return str;
}

void ByteStream::end_input() { flag_end = true;}

bool ByteStream::input_ended() const { return flag_end; }

size_t ByteStream::buffer_size() const { return cache.size(); }

bool ByteStream::buffer_empty() const { return cache.empty(); }

bool ByteStream::eof() const { return cache.empty() && input_ended(); }

size_t ByteStream::bytes_written() const { return write_size; }

size_t ByteStream::bytes_read() const { return read_size; }

size_t ByteStream::remaining_capacity() const { return _capacity - cache.size(); }

