#include "Os/Stub/test/File.hpp"
#include "Os/File.hpp"
#include <new>
namespace Os {
namespace Stub {
namespace File {
namespace Test {

StaticData StaticData::data;

void StaticData::setNextStatus(Os::File::Status status) {
    StaticData::data.openStatus = status;
    StaticData::data.sizeStatus = status;
    StaticData::data.positionStatus = status;
    StaticData::data.preallocateStatus = status;
    StaticData::data.seekStatus = status;
    StaticData::data.flushStatus = status;
    StaticData::data.readStatus = status;
    StaticData::data.writeStatus = status;
}

void StaticData::setSizeResult(FwSizeType size) {
    StaticData::data.sizeResult = size;
}

void StaticData::setPositionResult(FwSizeType position) {
    StaticData::data.positionResult = position;
}

void StaticData::setReadResult(U8 *buffer, FwSizeType size) {
    StaticData::data.readResult = buffer;
    StaticData::data.readResultSize = size;
}

void StaticData::setReadSize(FwSizeType size) {
    StaticData::data.readSizeResult = size;
}

void StaticData::setWriteResult(U8 *buffer, FwSizeType size) {
    StaticData::data.writeResult = buffer;
    StaticData::data.writeResultSize = size;
}

void StaticData::setWriteSize(FwSizeType size) {
    StaticData::data.writeSizeResult = size;
}

TestFile::TestFile() {
    StaticData::data.lastCalled = StaticData::CONSTRUCT_FN;
}

TestFile::~TestFile() {
    StaticData::data.lastCalled = StaticData::DESTRUCT_FN;
}

FileInterface::Status TestFile::open(const char *filepath, Mode open_mode, OverwriteType overwrite) {
    StaticData::data.openPath = filepath;
    StaticData::data.openMode = open_mode;
    StaticData::data.openOverwrite = overwrite;
    StaticData::data.lastCalled = StaticData::OPEN_FN;
    StaticData::data.pointer = 0;
    return StaticData::data.openStatus;
}

void TestFile::close() {
    StaticData::data.lastCalled = StaticData::CLOSE_FN;
}

FileInterface::Status TestFile::size(FwSizeType& size_result) {
    StaticData::data.lastCalled = StaticData::SIZE_FN;
    size_result = StaticData::data.sizeResult;
    return StaticData::data.sizeStatus;
}

FileInterface::Status TestFile::position(FwSizeType& position_result) {
    StaticData::data.lastCalled = StaticData::POSITION_FN;
    position_result = StaticData::data.positionResult;
    return StaticData::data.positionStatus;
}

FileInterface::Status TestFile::preallocate(FwSizeType offset, FwSizeType length) {
    StaticData::data.preallocateOffset = offset;
    StaticData::data.preallocateLength = length;
    StaticData::data.lastCalled = StaticData::PREALLOCATE_FN;
    return StaticData::data.preallocateStatus;
}

FileInterface::Status TestFile::seek(FwSignedSizeType offset, SeekType seekType) {
    StaticData::data.seekOffset = offset;
    StaticData::data.seekType = seekType;
    StaticData::data.lastCalled = StaticData::SEEK_FN;
    return StaticData::data.seekStatus;
}

FileInterface::Status TestFile::flush() {
    StaticData::data.lastCalled = StaticData::FLUSH_FN;
    return StaticData::data.flushStatus;
}

FileInterface::Status TestFile::read(U8 *buffer, FwSizeType &size, WaitType wait) {
    StaticData::data.readBuffer = buffer;
    StaticData::data.readSize = size;
    StaticData::data.readWait = wait;
    StaticData::data.lastCalled = StaticData::READ_FN;
    // Copy read data if set
    if (nullptr != StaticData::data.readResult) {
        size = FW_MIN(size, StaticData::data.readResultSize - StaticData::data.pointer);
        (void) ::memcpy(buffer, StaticData::data.readResult + StaticData::data.pointer, static_cast<size_t>(size));
        StaticData::data.pointer += size;
    } else {
        size = StaticData::data.readSizeResult;
    }
    return StaticData::data.readStatus;
}

FileInterface::Status TestFile::write(const U8* buffer, FwSizeType &size, WaitType wait) {
    StaticData::data.writeBuffer = buffer;
    StaticData::data.writeSize = size;
    StaticData::data.writeWait = wait;
    StaticData::data.lastCalled = StaticData::WRITE_FN;
    // Copy read data if set
    if (nullptr != StaticData::data.writeResult) {
        size = FW_MIN(size, StaticData::data.writeResultSize - StaticData::data.pointer);
        (void) ::memcpy(StaticData::data.writeResult + StaticData::data.pointer, buffer, static_cast<size_t>(size));
        StaticData::data.pointer += size;
    } else {
        size = StaticData::data.writeSizeResult;
    }
    return StaticData::data.writeStatus;
}

FileHandle* TestFile::getHandle() {
    return &this->m_handle;
}

} // namespace Test
} // namespace File
} // namespace Stub
} // namespace Os
