// Copyright 2013 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef NINJA_POINTER_VECTOR_H_
#define NINJA_POINTER_VECTOR_H_

/// PointerVector holds a collection of pointers.
/// It has some internal space for pointers (so it doesn't use any allocation
/// for small quantities of pointers) and then spills over into allocating
/// a buffer if it needs more space.
template<typename T>
struct PointerVector {
  /// How many pointers to inline.
  static const int kInlineSize = 4;

  /// How many pointers to resize to if we resize.
  static const int kGrowSize = 64;

  /// Count of stored pointers.
  int len_;

  /// Capacity before needing a resize.
  int cap_;

  /// The data, whether inlined or allocated.
  T** data_;

  /// The initial space for storing pointers.
  T* inline_data_[kInlineSize];

  typedef T** iterator;
  typedef T* const * const_iterator;

  PointerVector() : len_(0), cap_(kInlineSize), data_(inline_data_) {}

  ~PointerVector() {
    if (data_ != inline_data_)
      delete [] data_;
  }

  /// Grow the amount of available space, adjusting cap_.
  void grow() {
    cap_ = cap_ < kGrowSize ? kGrowSize : cap_ * 2;
    T** new_data = new T*[cap_];
    memcpy(new_data, data_, len_ * sizeof(T*));
    if (data_ != inline_data_)
      delete [] data_;
    data_ = new_data;
  }

  void push_back(T* data) {
    if (len_ == cap_)
      grow();
    data_[len_] = data;
    ++len_;
  }

  iterator begin() { return data_;}
  iterator end() { return data_ + len_; }
  const_iterator begin() const { return const_cast<const_iterator>(begin()); }
  const_iterator end() const { return const_cast<const_iterator>(end()); }

  size_t size() const {
    return len_;
  }

  bool empty() const {
    return len_ == 0;
  }

  T*& operator[](int i) const {
    return data_[i];
  }

  /// Insert space for \a count entries at offset \a offset.
  void make_space(int offset, int count) {
    while (len_ + count > cap_) {
      grow();
    }
    memmove(data_ + offset + count, data_ + offset,
            (len_ - offset) * sizeof(T*));
    len_ += count;
  }
};

#endif  // NINJA_POINTER_VECTOR_H_
