#ifndef STORAGE_LEVELDB_INCLUDE_STATUS_H_
#define STORAGE_LEVELDB_INCLUDE_STATUS_H_

#include <algorithm>
#include <string>

#include "leveldb/export.h"
#include "leveldb/slice.h"

namespace leveldb {
    class LEVELDB_EXPORT Status {
        public:
            Status() noexcept : state_(nullptr) {}
            ~Status() { delete[] state_; }

            Status(const Status& rhs);
            Status& operator=(const Status& rhs);

            Status(Status&& rhs) noexcept : state_(rhs.state_) { rhs.state_ = nullptr; }
            Status& operator=(Status&& rhs) noexcept;

            static Status OK() { return Status(); }

            static Status NotFound(const Slice& msg, const Slice& msg2 = Slice()) {
                return Status(kNotFound, msg, msg2);
            }

            static Status Corruption(const Slice& msg, const Slice& msg2 = Slice()) {
                return Status(kCorruption, msg, msg2);
            }

            static Status NotSupported(const Slice& msg, const Slice& msg2 = Slice()) {
                return Status(kNotSupported, msg, msg2);
            }

            static Status InvalidArgument(const Slice& msg, const Slice& msg2 = Slice()) {
                return Status(kInvalidArgument, msg, msg2);
            }

            static Status IOError(const Slice& msg, const Slice& msg2 = Slice()) {
                return Status(kIOError, msg, msg2);
            }

            bool ok() const { return (state_ == nullptr); }

            bool IsNotFound() const { return code() == kNotFound; }

            bool IsIOError() const { return code() == kIOError; }

            bool IsNotSupportedError() const { return code() == kNotSupported; }

            bool IsInvalidArgument() const { return code() == kInvalidArgument; }

            std::string ToString() const;

        private:
            enum Code {
                kOk = 0,
                kNotFound = 1,
                kCorruption = 2,
                kNotSupported = 3,
                kInvalidArgument = 4,
                kIOError = 5
            };

            Code code() const {
                return (state_ == nullptr) ? kOk : static_cast<Code>(state_[4]);
            }

            Status(Code code, const Slice& msg, const Slice& msg2);
            static const char* CopyState(const char* s);

            // OK -> null
            // Else state_[0...3] -> length of message
            // state_[4] -> code
            // state_[5...] -> message
            const char* state_;
    };

    inline Status::Status(const Status& rhs) {
        state_ = (rhs.state_ == nullptr) ? nullptr : CopyState(rhs.state_);
    }

    inline Status& Status::operator=(const Status& rhs) {
        if (state_ != rhs.state_) {
            delete[] state_;
            state_ = (rhs.state_ == nullptr) ? nullptr : CopyState(rhs.state_);
        }

        return *this;
    }

    inline Status& Status::operator=(Status&& rhs) noexcept {
        std::swap(state_, rhs.state_);
        return *this;
    }     
}

#endif
