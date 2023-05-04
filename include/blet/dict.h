/**
 * dict.h
 *
 * Licensed under the MIT License <http://opensource.org/licenses/MIT>.
 * Copyright (c) 2022-2023 BLET Mickaël.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _BLET_DICT_H_
#define _BLET_DICT_H_

#include <deque>     // std::deque
#include <exception> // std::exception
#include <list>      // std::list
#include <map>       // std::map
#include <queue>     // std::queue
#include <set>       // std::set
#include <sstream>   // std::istream, std::ostream, std:ostringstream
#include <stack>     // std::stack
#include <string>    // std::string
#include <vector>    // std::vector

namespace blet {

/**
 * @brief Dictionnary class for use boolean or number or string or array or object(map).
 */
class Dict {
  public:
    typedef bool boolean_t;
    typedef double number_t;
    typedef std::string string_t;
    typedef std::vector<Dict> array_t;
    typedef std::map<std::string, Dict> object_t;

    /**
     * @brief Enum of support type.
     */
    enum EType {
        NULL_TYPE = 0,
        BOOLEAN_TYPE,
        NUMBER_TYPE,
        STRING_TYPE,
        ARRAY_TYPE,
        OBJECT_TYPE
    };

    // -------------------------------------------------------------------------
    //  ........................................
    //  .%%..%%..%%..%%..%%%%%%...%%%%...%%..%%.
    //  .%%..%%..%%%.%%....%%....%%..%%..%%%.%%.
    //  .%%..%%..%%.%%%....%%....%%..%%..%%.%%%.
    //  .%%..%%..%%..%%....%%....%%..%%..%%..%%.
    //  ..%%%%...%%..%%..%%%%%%...%%%%...%%..%%.
    //  ........................................
    // -------------------------------------------------------------------------

    /**
     * @brief Union of value.
     */
    union UValue {
      private:
        boolean_t _boolean;
        number_t _number;
        string_t* _string;
        array_t* _array;
        object_t* _object;

      public:
        /**
         * @brief Construct a new UValue with boolean at false.
         */
        UValue() :
            _boolean(false) {}
        /**
         * @brief Construct a new UValue with a boolean.
         */
        UValue(const boolean_t& value) :
            _boolean(value) {}
        /**
         * @brief Construct a new UValue with a number.
         */
        template<typename T>
        UValue(const T& value) :
            _number(value) {}
        /**
         * @brief Construct a new UValue with a string.
         */
        UValue(const std::string& value) :
            _string(new string_t(value)) {}
        /**
         * @brief Construct a new UValue with a string.
         */
        UValue(const char* value) :
            _string(new string_t(value)) {}
        /**
         * @brief Construct a new UValue with a string.
         */
        template<std::size_t Size>
        UValue(const char (&value)[Size]) :
            _string(new string_t(value)) {}
        /**
         * @brief Construct a new UValue with a array.
         */
        template<typename T>
        UValue(const std::deque<T>& value) :
            _array(new array_t()) {
            typename std::deque<T>::const_iterator it;
            for (it = value.begin(); it != value.end(); ++it) {
                _array->push_back(*it);
            }
        }
        /**
         * @brief Construct a new UValue with a array.
         */
        template<typename T>
        UValue(const std::list<T>& value) :
            _array(new array_t()) {
            typename std::list<T>::const_iterator it;
            for (it = value.begin(); it != value.end(); ++it) {
                _array->push_back(*it);
            }
        }
        /**
         * @brief Construct a new UValue with a array.
         */
        template<typename T, typename U>
        UValue(const std::map<T, U>& value) :
            _array(new array_t()) {
            typename std::map<T, U>::const_iterator it;
            for (it = value.begin(); it != value.end(); ++it) {
                if (static_cast<std::size_t>(it->first) < _array->size()) {
                    (*_array)[static_cast<std::size_t>(it->first)] = it->second;
                    continue;
                }
                while (_array->size() < static_cast<std::size_t>(it->first)) {
                    _array->push_back(Dict());
                }
                _array->push_back(it->second);
            }
        }
        /**
         * @brief Construct a new UValue with a array.
         */
        template<typename T>
        UValue(const std::queue<T>& value) :
            _array(new array_t()) {
            std::queue<T> copy = value;
            while (!copy.empty()) {
                _array->push_back(copy.front());
                copy.pop();
            }
        }
        /**
         * @brief Construct a new UValue with a array.
         */
        template<typename T>
        UValue(const std::set<T>& value) :
            _array(new array_t()) {
            typename std::set<T>::const_iterator it;
            for (it = value.begin(); it != value.end(); ++it) {
                _array->push_back(*it);
            }
        }
        /**
         * @brief Construct a new UValue with a array.
         */
        template<typename T>
        UValue(const std::stack<T>& value) :
            _array(new array_t()) {
            std::stack<T> copy = value;
            while (!copy.empty()) {
                _array->push_back(copy.top());
                copy.pop();
            }
        }
        /**
         * @brief Construct a new UValue with a array.
         */
        template<typename T>
        UValue(const std::vector<T>& value) :
            _array(new array_t()) {
            typename std::vector<T>::const_iterator it;
            for (it = value.begin(); it != value.end(); ++it) {
                _array->push_back(*it);
            }
        }
        /**
         * @brief Construct a new UValue with a object.
         */
        template<typename T>
        UValue(const std::map<std::string, T>& value) :
            _object(new object_t()) {
            typename std::map<std::string, T>::const_iterator it;
            for (it = value.begin(); it != value.end(); ++it) {
                _object->insert(std::pair<std::string, Dict>(it->first, it->second));
            }
        }

        /**
         * @brief Return boolean_t& Reference of boolean.
         */
        boolean_t& getBoolean() {
            return _boolean;
        }

        /**
         * @brief Return const boolean_t& Const reference of boolean.
         */
        const boolean_t& getBoolean() const {
            return _boolean;
        }

        /**
         * @brief Return number_t& Reference of number.
         */
        number_t& getNumber() {
            return _number;
        }

        /**
         * @brief Return const number_t& Const reference of number.
         */
        const number_t& getNumber() const {
            return _number;
        }

        /**
         * @brief Return reference of string.
         */
        string_t& getString() {
            return *_string;
        }

        /**
         * @brief Return the read-only (constant) reference of string.
         */
        const string_t& getString() const {
            return *_string;
        }

        /**
         * @brief Return reference of array.
         */
        array_t& getArray() {
            return *_array;
        }

        /**
         * @brief Return the read-only (constant) reference of array.
         */
        const array_t& getArray() const {
            return *_array;
        }

        /**
         * @brief Return reference of object.
         */
        object_t& getObject() {
            return *_object;
        }

        /**
         * @brief Return the read-only (constant) reference of object.
         */
        const object_t& getObject() const {
            return *_object;
        }

        /**
         * @brief New String.
         * Use the new operator of string with @a value.
         *
         * @param value Source string to use.
         */
        void newString(const string_t& value = string_t()) {
            _string = new string_t(value);
        }

        /**
         * @brief New Array.
         * Use the new operator of array with @a value.
         *
         * @param value Source array to use.
         */
        void newArray(const array_t& value = array_t()) {
            _array = new array_t(value);
        }

        /**
         * @brief New Object.
         * Use the new operator of object with @a value.
         *
         * @param value Source object to use.
         */
        void newObject(const object_t& value = object_t()) {
            _object = new object_t(value);
        }

        /**
         * @brief Delete String.
         */
        void delString() {
            delete _string;
        }

        /**
         * @brief Delete Array.
         */
        void delArray() {
            delete _array;
        }

        /**
         * @brief Delete Object.
         */
        void delObject() {
            delete _object;
        }
    };

  protected:
    EType _type;
    UValue _value;

  public:
    // -------------------------------------------------------------------------
    //  ........................................................................
    //  .%%%%%%..%%..%%...%%%%...%%%%%%..%%%%%...%%%%%%..%%%%%%...%%%%...%%..%%.
    //  .%%.......%%%%...%%..%%..%%......%%..%%....%%......%%....%%..%%..%%%.%%.
    //  .%%%%......%%....%%......%%%%....%%%%%.....%%......%%....%%..%%..%%.%%%.
    //  .%%.......%%%%...%%..%%..%%......%%........%%......%%....%%..%%..%%..%%.
    //  .%%%%%%..%%..%%...%%%%...%%%%%%..%%........%%....%%%%%%...%%%%...%%..%%.
    //  ........................................................................
    // -------------------------------------------------------------------------

    /**
     * @brief Exception from std::exception.
     */
    class Exception : public std::exception {
      public:
        /**
         * @brief Construct a new Exception object.
         * The @a message is return when what() method is called.
         *
         * @param message A message.
         */
        Exception(const std::string& message) :
            std::exception(),
            _message(message) {}
        /**
         * @brief Destroy the Exception object.
         */
        virtual ~Exception() throw() {}
        /**
         * @brief Return a C-style character string describing the general cause of the current error.
         */
        const char* what() const throw() {
            return _message.c_str();
        }

      protected:
        std::string _message;
    };

    /**
     * @brief Access exception from Exception.
     */
    class AccessException : public Exception {
      public:
        /**
         * @brief Construct a new Access Exception object.
         *
         * @param dict A dictionnary.
         * @param message A message.
         */
        AccessException(const Dict& dict, const std::string& message) :
            Exception(message + " (is " + Dict::typeToStr(dict.getType()) + ")."),
            _dict(dict) {}

        /**
         * @brief Destroy the Access Exception object.
         */
        virtual ~AccessException() throw() {}

        /**
         * @brief Return the read-only (constant) reference dictionnary object.
         */
        const Dict& dict() const throw() {
            return _dict;
        }

      protected:
        const Dict& _dict;
    };

    /**
     * @brief Child exception from AccessException.
     */
    class ChildException : public AccessException {
      public:
        /**
         * @brief Construct a new Child Exception object.
         *
         * @param dict A dictionnary.
         * @param index A message.
         */
        ChildException(const Dict& dict, unsigned long index) :
            AccessException(dict, ""),
            _index(index),
            _key() {
            std::ostringstream oss("");
            oss << index << " has out of range.";
            _message = oss.str();
        }

        /**
         * @brief Construct a new Child Exception object
         *
         * @param dict A dictionnary.
         * @param key A key.
         */
        ChildException(const Dict& dict, const std::string& key) :
            AccessException(dict, ""),
            _index(0),
            _key(key) {
            std::ostringstream oss("");
            oss << key << " has not a key.";
            _message = oss.str();
        }

        /**
         * @brief Destroy the Child Exception object.
         */
        virtual ~ChildException() throw() {}

        /**
         * @brief Return the read-only (constant) reference key.
         */
        const std::string& key() const throw() {
            return _key;
        }

        /**
         * @brief Return the read-only (constant) reference index.
         */
        const unsigned long& index() const throw() {
            return _index;
        }

      protected:
        unsigned long _index;
        std::string _key;
    };

    /**
     * @brief Method exception from AccessException
     */
    class MethodException : public AccessException {
      public:
        /**
         * @brief Construct a new Method Exception object.
         *
         * @param dict A dictionnary.
         * @param methodName A method name.
         */
        MethodException(const Dict& dict, const std::string& methodName) :
            AccessException(dict, ""),
            _methodName(methodName) {
            std::ostringstream oss("");
            oss << "has not a method " << _methodName << ".";
            _message = oss.str();
        }

        /**
         * @brief Destroy the Method Exception object.
         */
        virtual ~MethodException() throw() {}

        /**
         * @brief Return the read-only (constant) reference methodName.
         */
        const std::string& methodName() const throw() {
            return _methodName;
        }

      protected:
        std::string _methodName;
    };

    /**
     * @brief Get the C string From EType.
     *
     * @param type Source type to use.
     * @return const char* C-style character string.
     */
    static const char* typeToStr(const EType& type) {
        const char* ret = NULL;
        switch (type) {
            case NULL_TYPE:
                ret = "null";
                break;
            case BOOLEAN_TYPE:
                ret = "boolean";
                break;
            case NUMBER_TYPE:
                ret = "number";
                break;
            case STRING_TYPE:
                ret = "string";
                break;
            case ARRAY_TYPE:
                ret = "array";
                break;
            case OBJECT_TYPE:
                ret = "object";
                break;
        }
        return ret;
    }

    /**
     * @brief Write dictionnary to a stream.
     *
     * @param os Output stream.
     * @param dict Dict to write out.
     * @return std::ostream& Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Dict& dict) {
        switch (dict._type) {
            case Dict::NULL_TYPE:
                os << "null";
                break;
            case Dict::BOOLEAN_TYPE:
                os << dict._value.getBoolean();
                break;
            case Dict::NUMBER_TYPE:
                os << dict._value.getNumber();
                break;
            case Dict::STRING_TYPE:
                os << dict._value.getString();
                break;
            case Dict::ARRAY_TYPE:
                os << "<array " << &dict << ">";
                break;
            case Dict::OBJECT_TYPE:
                os << "<object " << &dict << ">";
                break;
        }
        return os;
    }

    /**
     * @brief Construct a new null Dict.
     */
    Dict() :
        _type(NULL_TYPE),
        _value() {}

    /**
     * @brief Construct a new object Dict.
     *
     * @param rhs Source dictionnary.
     */
    Dict(const Dict& rhs) :
        _type(rhs._type) {
        switch (_type) {
            case NULL_TYPE:
            case BOOLEAN_TYPE:
            case NUMBER_TYPE:
                _value = rhs._value;
                break;
            case STRING_TYPE:
                _value.newString(rhs._value.getString());
                break;
            case ARRAY_TYPE:
                _value.newArray(rhs._value.getArray());
                break;
            case OBJECT_TYPE:
                _value.newObject(rhs._value.getObject());
                break;
        }
    }

    /**
     * @brief Construct a new boolean Dict.
     *
     * @param value Source boolean.
     */
    Dict(const boolean_t& value) :
        _type(BOOLEAN_TYPE),
        _value(value) {}

    /**
     * @brief Construct a new number Dict.
     *
     * @tparam T Type of argument.
     * @param value Source argument.
     */
    template<typename T>
    Dict(const T& value) :
        _type(NUMBER_TYPE),
        _value(value) {}

    /**
     * @brief Construct a new string Dict.
     *
     * @param value Source string.
     */
    Dict(const std::string& value) :
        _type(STRING_TYPE),
        _value(value) {}

    /**
     * @brief Construct a new string Dict.
     *
     * @param value Source C string.
     */
    Dict(const char* value) :
        _type(STRING_TYPE),
        _value(value) {}

    /**
     * @brief Construct a new string Dict.
     *
     * @tparam Size of string.
     */
    template<std::size_t Size>
    Dict(const char (&value)[Size]) :
        _type(STRING_TYPE),
        _value(value) {}

    /**
     * @brief Construct a new array Dict.
     *
     * @tparam T Type of template.
     * @param value A deque.
     */
    template<typename T>
    Dict(const std::deque<T>& value) :
        _type(ARRAY_TYPE),
        _value(value) {}

    /**
     * @brief Construct a new array Dict.
     *
     * @tparam T Type of template.
     * @param value A list.
     */
    template<typename T>
    Dict(const std::list<T>& value) :
        _type(ARRAY_TYPE),
        _value(value) {}

    /**
     * @brief Construct a new array Dict.
     *
     * @tparam T Type of key.
     * @tparam U Type of value.
     * @param value A map.
     */
    template<typename T, typename U>
    Dict(const std::map<T, U>& value) :
        _type(ARRAY_TYPE),
        _value(value) {}

    /**
     * @brief Construct a new array Dict.
     *
     * @tparam T Type of template.
     * @param value A queue.
     */
    template<typename T>
    Dict(const std::queue<T>& value) :
        _type(ARRAY_TYPE),
        _value(value) {}

    /**
     * @brief Construct a new array Dict.
     *
     * @tparam T Type of template.
     * @param value A set.
     */
    template<typename T>
    Dict(const std::set<T>& value) :
        _type(ARRAY_TYPE),
        _value(value) {}

    /**
     * @brief Construct a new array Dict.
     *
     * @tparam T Type of template.
     * @param value A stack.
     */
    template<typename T>
    Dict(const std::stack<T>& value) :
        _type(ARRAY_TYPE),
        _value(value) {}

    /**
     * @brief Construct a new array Dict.
     *
     * @tparam T Type of template.
     * @param value A vector.
     */
    template<typename T>
    Dict(const std::vector<T>& value) :
        _type(ARRAY_TYPE),
        _value(value) {}

    /**
     * @brief Construct a new object Dict.
     *
     * @tparam T Type of template.
     * @param value A map.
     */
    template<typename T>
    Dict(const std::map<std::string, T>& value) :
        _type(OBJECT_TYPE),
        _value(value) {}

    /**
     * @brief Destroy the Dict object.
     */
    ~Dict() {
        switch (_type) {
            case NULL_TYPE:
            case BOOLEAN_TYPE:
            case NUMBER_TYPE:
                break;
            case STRING_TYPE:
                _value.delString();
                break;
            case ARRAY_TYPE:
                _value.delArray();
                break;
            case OBJECT_TYPE:
                _value.delObject();
                break;
        }
    }

    /**
     * @brief Replace dict.
     *
     * @param dict A dictionnary.
     * @return Dict& Reference of object.
     */
    Dict& operator=(const Dict& dict) {
        if (&dict == this) {
            return *this;
        }
        clear();
        switch (dict._type) {
            case NULL_TYPE:
                break;
            case BOOLEAN_TYPE:
            case NUMBER_TYPE:
                _value = dict._value;
                break;
            case STRING_TYPE:
                _value.newString(dict._value.getString());
                break;
            case ARRAY_TYPE:
                _value.newArray(dict._value.getArray());
                break;
            case OBJECT_TYPE:
                _value.newObject(dict._value.getObject());
                break;
        }
        _type = dict._type;
        return *this;
    }

    /**
     * @brief Copy dict if isNull().
     *
     * @param dict A dictionnary.
     * @return Dict& Reference of object.
     */
    Dict& operator<<=(const Dict& dict) {
        if (&dict == this) {
            return *this;
        }
        if (!isNull()) {
            throw AccessException(*this, "is not null");
        }
        switch (dict._type) {
            case NULL_TYPE:
                break;
            case BOOLEAN_TYPE:
            case NUMBER_TYPE:
                _value = dict._value;
                break;
            case STRING_TYPE:
                _value.newString(dict._value.getString());
                break;
            case ARRAY_TYPE:
                _value.newArray(dict._value.getArray());
                break;
            case OBJECT_TYPE:
                _value.newObject(dict._value.getObject());
                break;
        }
        _type = dict._type;
        return *this;
    }

    /**
     * @brief Get the Type object (unsafe).
     *
     * @return EType& Reference of type.
     */
    EType& getType() {
        return _type;
    }

    /**
     * @brief Get the Type object.
     *
     * @return const EType& the read-only (constant) reference of type.
     */
    const EType& getType() const {
        return _type;
    }


    /**
     * @brief Get the Value object (unsafe)
     *
     * @return UValue& Reference of value.
     */
    UValue& getValue() {
        return _value;
    }

    /**
     * @brief Get the Value object
     *
     * @return UValue& the read-only (constant) reference of value.
     */
    const UValue& getValue() const {
        return _value;
    }

    /**
     * @brief Swap object.
     *
     * @param dict A dictionnary.
     */
    void swap(Dict& dict) {
        EType tmpType = _type;
        UValue tmpValue = _value;
        _type = dict._type;
        _value = dict._value;
        dict._type = tmpType;
        dict._value = tmpValue;
    }

    /**
     * @brief Clear dict and set type as null.
     */
    void clear() {
        switch (_type) {
            case NULL_TYPE:
            case BOOLEAN_TYPE:
            case NUMBER_TYPE:
                break;
            case STRING_TYPE:
                _value.delString();
                break;
            case ARRAY_TYPE:
                _value.delArray();
                break;
            case OBJECT_TYPE:
                _value.delObject();
                break;
        }
        _type = NULL_TYPE;
    }

    // -------------------------------------------------------------------------
    //  ................................
    //  .%%..%%..%%..%%..%%......%%.....
    //  .%%%.%%..%%..%%..%%......%%.....
    //  .%%.%%%..%%..%%..%%......%%.....
    //  .%%..%%..%%..%%..%%......%%.....
    //  .%%..%%...%%%%...%%%%%%..%%%%%%.
    //  ................................
    // -------------------------------------------------------------------------

    /**
     * @brief Return true if type is null else false.
     */
    bool isNull() const {
        return _type == NULL_TYPE;
    }

    /**
     * @brief Create null.
     *
     * @throw AccessException if type is not a null.
     */
    void newNull() const {
        if (!isNull()) {
            throw AccessException(*this, "is not a null");
        }
    }

    // -------------------------------------------------------------------------
    //  ........................................................
    //  .%%%%%....%%%%....%%%%...%%......%%%%%%...%%%%...%%..%%.
    //  .%%..%%..%%..%%..%%..%%..%%......%%......%%..%%..%%%.%%.
    //  .%%%%%...%%..%%..%%..%%..%%......%%%%....%%%%%%..%%.%%%.
    //  .%%..%%..%%..%%..%%..%%..%%......%%......%%..%%..%%..%%.
    //  .%%%%%....%%%%....%%%%...%%%%%%..%%%%%%..%%..%%..%%..%%.
    //  ........................................................
    // -------------------------------------------------------------------------

    /**
     * @brief Return true if type is boolean else false.
     */
    bool isBoolean() const {
        return _type == BOOLEAN_TYPE;
    }

    /**
     * @brief Get the boolean of dict.
     *
     * @return boolean_t& Reference to this boolean.
     * @throw AccessException if dict type is not null or not a boolean.
     */
    boolean_t& getBoolean() {
        if (!isNull() && !isBoolean()) {
            throw AccessException(*this, "is not a boolean");
        }
        if (isNull()) {
            _type = BOOLEAN_TYPE;
            _value.getBoolean() = false;
        }
        return _value.getBoolean();
    }

    /**
     * @brief Get the boolean of dict.
     *
     * @return const boolean_t& Read-only (constant) reference to this boolean.
     * @throw AccessException if dict type is not a boolean.
     */
    const boolean_t& getBoolean() const {
        if (!isBoolean()) {
            throw AccessException(*this, "is not a boolean");
        }
        return _value.getBoolean();
    }

    /**
     * @brief Set value from bool.
     *
     * @param value New value.
     * @return Dict& Reference to this dictionnary.
     * @throw AccessException if type is not null or not a boolean.
     */
    Dict& operator=(const boolean_t& value) {
        newBoolean<boolean_t>(value);
        return *this;
    }

    /**
     * @brief Convert to boolean.
     *
     * @return const boolean_t& Read-only (constant) reference to this boolean.
     * @throw AccessException if type is not a boolean.
     */
    operator const boolean_t&() const {
        return getBoolean();
    }

    /**
     * @brief Create bool from @p value.
     *
     * @tparam T Type of value.
     * @param value New value.
     * @throw AccessException if type is not a null and not a boolean.
     */
    template<typename T>
    void newBoolean(const T& value) {
        if (!isNull() && !isBoolean()) {
            throw AccessException(*this, "is not a boolean");
        }
        _type = BOOLEAN_TYPE;
        _value.getBoolean() = value;
    }

    /**
     * @brief Boolean equality comparison.
     *
     * @param value A boolean.
     * @return True if dict is boolean and with value are equal.
     */
    bool operator==(const boolean_t& value) const {
        bool ret;
        switch (_type) {
            case NULL_TYPE:
            case NUMBER_TYPE:
            case STRING_TYPE:
            case ARRAY_TYPE:
            case OBJECT_TYPE:
                ret = false;
                break;
            case BOOLEAN_TYPE:
                ret = _value.getBoolean() == value;
                break;
        }
        return ret;
    }

    /**
     * @brief Boolean not equality comparison.
     *
     * @param value A boolean.
     * @return True if dict and value is not equal.
     */
    bool operator!=(const boolean_t& value) const {
        return !(operator==(value));
    }

    /**
     * @brief Boolean ordering relation.
     *
     * @param value A boolean.
     * @return True if dict is boolean and is lexicographically greater than value.
     */
    bool operator>(const boolean_t& value) const {
        bool ret;
        switch (_type) {
            case NULL_TYPE:
            case NUMBER_TYPE:
            case STRING_TYPE:
            case ARRAY_TYPE:
            case OBJECT_TYPE:
                ret = false;
                break;
            case BOOLEAN_TYPE:
                ret = _value.getBoolean() > value;
                break;
        }
        return ret;
    }

    /**
     * @brief Boolean ordering relation.
     *
     * @param value A boolean.
     * @return True if dict is boolean and is lexicographically less than value.
     */
    bool operator<(const boolean_t& value) const {
        bool ret;
        switch (_type) {
            case NULL_TYPE:
            case NUMBER_TYPE:
            case STRING_TYPE:
            case ARRAY_TYPE:
            case OBJECT_TYPE:
                ret = false;
                break;
            case BOOLEAN_TYPE:
                ret = _value.getBoolean() < value;
                break;
        }
        return ret;
    }

    /**
     * @brief Boolean ordering relation.
     *
     * @param value A boolean.
     * @return True if dict is boolean and is lexicographically greater or equal than value.
     */
    bool operator>=(const boolean_t& value) const {
        bool ret;
        switch (_type) {
            case NULL_TYPE:
            case NUMBER_TYPE:
            case STRING_TYPE:
            case ARRAY_TYPE:
            case OBJECT_TYPE:
                ret = false;
                break;
            case BOOLEAN_TYPE:
                ret = _value.getBoolean() >= value;
                break;
        }
        return ret;
    }

    /**
     * @brief Boolean ordering relation.
     *
     * @param value A boolean.
     * @return True if dict is boolean and is lexicographically less or equal than value.
     */
    bool operator<=(const boolean_t& value) const {
        bool ret;
        switch (_type) {
            case NULL_TYPE:
            case NUMBER_TYPE:
            case STRING_TYPE:
            case ARRAY_TYPE:
            case OBJECT_TYPE:
                ret = false;
                break;
            case BOOLEAN_TYPE:
                ret = _value.getBoolean() <= value;
                break;
        }
        return ret;
    }

    // -------------------------------------------------------------------------
    //  .................................................
    //  .%%..%%..%%..%%..%%...%%..%%%%%...%%%%%%..%%%%%..
    //  .%%%.%%..%%..%%..%%%.%%%..%%..%%..%%......%%..%%.
    //  .%%.%%%..%%..%%..%%.%.%%..%%%%%...%%%%....%%%%%..
    //  .%%..%%..%%..%%..%%...%%..%%..%%..%%......%%..%%.
    //  .%%..%%...%%%%...%%...%%..%%%%%...%%%%%%..%%..%%.
    //  .................................................
    // -------------------------------------------------------------------------

    /**
     * @brief Return true if type is number else false.
     */
    bool isNumber() const {
        return _type == NUMBER_TYPE;
    }

    /**
     * @brief Get the number of dict.
     *
     * @return number_t& Reference to this number.
     * @throw AccessException if dict type is not null or not a number.
     */
    number_t& getNumber() {
        if (!isNull() && !isNumber()) {
            throw AccessException(*this, "is not a number");
        }
        if (isNull()) {
            _type = NUMBER_TYPE;
            _value.getNumber() = 0.0;
        }
        return _value.getNumber();
    }

    /**
     * @brief Get the number of dict.
     *
     * @return const number_t& Read-only (constant) reference to this number.
     * @throw AccessException if dict type is not a number.
     */
    const number_t& getNumber() const {
        if (!isNumber()) {
            throw AccessException(*this, "is not a number");
        }
        return _value.getNumber();
    }

    /**
     * @brief Set value from number.
     *
     * @tparam T Type of template.
     * @param value New value.
     * @return Dict& Reference to this dictionnary.
     * @throw AccessException if type is not null or not a number.
     */
    template<typename T>
    Dict& operator=(const T& value) {
        newNumber(value);
        return *this;
    }

    /**
     * @brief Convert to number.
     *
     * @tparam T Type of template.
     * @return Number of this dictionnary.
     * @throw AccessException if type is not a number.
     */
    template<typename T>
    operator T() const {
        return getNumber();
    }

    /**
     * @brief Create number from @p value.
     *
     * @tparam T Type of value.
     * @param value New value.
     * @throw AccessException if type is not a null and not a number.
     */
    template<typename T>
    void newNumber(const T& value) {
        if (!isNull() && !isNumber()) {
            throw AccessException(*this, "is not a number");
        }
        _type = NUMBER_TYPE;
        _value.getNumber() = value;
    }

    /**
     * @brief Number equality comparison.
     *
     * @tparam T Type of number.
     * @param value A number.
     * @return True if the value and the dict are equal.
     */
    template<typename T>
    bool operator==(const T& value) const {
        bool ret;
        switch (_type) {
            case NULL_TYPE:
            case BOOLEAN_TYPE:
            case STRING_TYPE:
            case ARRAY_TYPE:
            case OBJECT_TYPE:
                ret = false;
                break;
            case NUMBER_TYPE:
                ret = _value.getNumber() == value;
                break;
        }
        return ret;
    }

    /**
     * @brief Number not equality comparison.
     *
     * @tparam T Type of template.
     * @param value A number.
     * @return True if dict and value is not equal.
     */
    template<typename T>
    bool operator!=(const T& value) const {
        return !(operator==(value));
    }

    /**
     * @brief Number ordering relation.
     *
     * @param value A number.
     * @return True if dict is number and is lexicographically greater than value.
     */
    template<typename T>
    bool operator>(const T& value) const {
        bool ret;
        switch (_type) {
            case NULL_TYPE:
            case ARRAY_TYPE:
            case BOOLEAN_TYPE:
            case STRING_TYPE:
            case OBJECT_TYPE:
                ret = false;
                break;
            case NUMBER_TYPE:
                ret = _value.getNumber() > value;
                break;
        }
        return ret;
    }

    /**
     * @brief Number ordering relation.
     *
     * @param value A number.
     * @return True if dict is number and is lexicographically less than value.
     */
    template<typename T>
    bool operator<(const T& value) const {
        bool ret;
        switch (_type) {
            case NULL_TYPE:
            case ARRAY_TYPE:
            case BOOLEAN_TYPE:
            case STRING_TYPE:
            case OBJECT_TYPE:
                ret = false;
                break;
            case NUMBER_TYPE:
                ret = _value.getNumber() < value;
                break;
        }
        return ret;
    }

    /**
     * @brief Number ordering relation.
     *
     * @param value A number.
     * @return True if dict is number and is lexicographically greater or equal than value.
     */
    template<typename T>
    bool operator>=(const T& value) const {
        bool ret;
        switch (_type) {
            case NULL_TYPE:
            case ARRAY_TYPE:
            case BOOLEAN_TYPE:
            case STRING_TYPE:
            case OBJECT_TYPE:
                ret = false;
                break;
            case NUMBER_TYPE:
                ret = _value.getNumber() >= value;
                break;
        }
        return ret;
    }

    /**
     * @brief Number ordering relation.
     *
     * @param value A number.
     * @return True if dict is number and is lexicographically less or equal than value.
     */
    template<typename T>
    bool operator<=(const T& value) const {
        bool ret;
        switch (_type) {
            case NULL_TYPE:
            case ARRAY_TYPE:
            case BOOLEAN_TYPE:
            case STRING_TYPE:
            case OBJECT_TYPE:
                ret = false;
                break;
            case NUMBER_TYPE:
                ret = _value.getNumber() <= value;
                break;
        }
        return ret;
    }

    // -------------------------------------------------------------------------
    //  ................................................
    //  ..%%%%...%%%%%%..%%%%%...%%%%%%..%%..%%...%%%%..
    //  .%%........%%....%%..%%....%%....%%%.%%..%%.....
    //  ..%%%%.....%%....%%%%%.....%%....%%.%%%..%%.%%%.
    //  .....%%....%%....%%..%%....%%....%%..%%..%%..%%.
    //  ..%%%%.....%%....%%..%%..%%%%%%..%%..%%...%%%%..
    //  ................................................
    // -------------------------------------------------------------------------

    /**
     * @brief Return true if type is a string else false.
     */
    bool isString() const {
        return _type == STRING_TYPE;
    }

    /**
     * @brief Get the string of dict.
     *
     * @return string_t& Reference to this string.
     * @throw AccessException If dict type is not null or not a string.
     */
    string_t& getString() {
        if (!isNull() && !isString()) {
            throw AccessException(*this, "is not a string");
        }
        if (isNull()) {
            _type = STRING_TYPE;
            _value.newString();
        }
        return _value.getString();
    }

    /**
     * @brief Get the string of dict.
     *
     * @return const string_t& Read-only (constant) reference to this string.
     * @throw AccessException If dict type is not a string.
     */
    const string_t& getString() const {
        if (!isString()) {
            throw AccessException(*this, "is not a string");
        }
        return _value.getString();
    }

    /**
     * @brief Set value from string.
     *
     * @param value New value.
     * @return Dict& Reference to this dictionnary.
     * @throw AccessException If type is not null or not a string.
     */
    Dict& operator=(const std::string& value) {
        newString<std::string>(value);
        return *this;
    }

    /**
     * @brief Set value from C string.
     *
     * @param value New value.
     * @return Dict& Reference to this dictionnary.
     * @throw AccessException If type is not null or not a string.
     */
    Dict& operator=(const char* value) {
        newString<std::string>(value);
        return *this;
    }

    /**
     * @brief Set value from string.
     *
     * @tparam Size Size of value.
     * @param value New value.
     * @return Dict& Reference to this dictionnary.
     * @throw AccessException If type is not null or not a string.
     */
    template<std::size_t Size>
    Dict& operator=(const char (&value)[Size]) {
        newString(std::string(value));
        return *this;
    }

    /**
     * @brief Convert to string.
     *
     * @return const string_t& String of this dictionnary.
     * @throw AccessException if dict type is not a string.
     */
    operator const string_t&() const {
        return getString();
    }

    /**
     * @brief Convert to C string.
     *
     * @return const char*  String of this dictionnary.
     * @throw AccessException if dict type is not a string.
     */
    operator const char*() const {
        return getString().c_str();
    }

    /**
     * @brief Create string from @p value.
     *
     * @param value New value.
     * @throw AccessException if type is not null or not a string.
     */
    void newString(const std::string& value) {
        if (!isNull() && !isString()) {
            throw AccessException(*this, "is not a string");
        }
        if (isNull()) {
            _type = STRING_TYPE;
            _value.newString(value);
        }
        else {
            _value.getString() = value;
        }
    }

    /**
     * @brief Create string from @p value with using << operator.
     *
     * @tparam T Type of value.
     * @param value New value.
     * @throw AccessException if type is not null or not a string.
     */
    template<typename T>
    void newString(const T& value) {
        if (!isNull() && !isString()) {
            throw AccessException(*this, "is not a string");
        }
        std::ostringstream oss("");
        oss << value;
        if (isNull()) {
            _type = STRING_TYPE;
            _value.newString(oss.str());
        }
        else {
            _value.getString() = oss.str();
        }
    }

    /**
     * @brief Append a string to this string.
     *
     * @param str The string to append.
     * @return Dict& Reference to this dictionnary.
     * @throw AccessException if dict type is not null or not a string.
     */
    Dict& append(const std::string& str) {
        getString().append(str);
        return *this;
    }

    /**
     * @brief Append a substring.
     * This function appends __n characters from __str starting at __pos to this string.
     * If __n is is larger than the number of available characters in __str, the remainder of __str is appended.
     *
     * @param __str The string to append.
     * @param __pos Index of the first character of str to append.
     * @param __n The number of characters to append.
     * @return Dict& Reference to this dictionnary.
     * @throw std::out_of_range if __pos is not a valid index.
     * @throw AccessException if dict type is not null or not a string.
     */
    Dict& append(const std::string& __str, std::size_t __pos, std::size_t __n = std::string::npos) {
        getString().append(__str, __pos, __n);
        return *this;
    }

    /**
     * @brief Append a C substring.
     *
     * @param __s The C string to append.
     * @param __n The number of characters to append.
     * @return Dict& Reference to this dictionnary.
     * @throw AccessException if dict type is not null or not a string.
     */
    Dict& append(const char* __s, std::size_t __n) {
        getString().append(__s, __n);
        return *this;
    }

    /**
     * @brief Append a C string.
     *
     * @param __s The C string to append.
     * @return Dict& Reference to this dictionnary.
     * @throw AccessException if dict type is not null or not a string.
     */
    Dict& append(const char* __s) {
        getString().append(__s);
        return *this;
    }

    /**
     * @brief Append multiple characters.
     * Appends __n copies of __c to this string.
     *
     * @param __n The number of characters to append.
     * @param __c The character to use.
     * @return Dict& Reference to this dictionnary.
     * @throw AccessException if dict type is not null or not a string.
     */
    Dict& append(std::size_t __n, char __c) {
        getString().append(__n, __c);
        return *this;
    }

    /**
     * @brief Append a range of characters.
     * Appends characters in the range (__first,__last) to this string.
     *
     * @tparam _InputIterator
     * @param __first Iterator referencing the first character to append.
     * @param __last Iterator marking the end of the range.
     * @return Dict& Reference to this dictionnary.
     * @throw AccessException if dict type is not null or not a string.
     */
    template<typename _InputIterator>
    Dict& string_append(_InputIterator __first, _InputIterator __last) {
        getString().append(__first, __last);
        return *this;
    }

    /**
     * @brief Set value to contents of another string.
     *
     * @param __str Source string to use.
     * @return Dict& Reference to this dictionnary.
     * @throw AccessException if type is not null or not a string.
     */
    Dict& assign(const std::string& __str) {
        getString().assign(__str);
        return *this;
    }

    /**
     * @brief Set value to a substring of a string.
     * This function sets this string to the substring of __str consisting of __n characters at __pos.
     * If __n is is larger than the number of available characters in __str, the remainder of __str is used.
     *
     * @param __str The string to use.
     * @param __pos Index of the first character of str.
     * @param __n Number of characters to use.
     * @return Dict& Reference to this dictionnary.
     * @throw std::out_of_range if pos is not a valid index.
     * @throw AccessException if type is not null or not a string.
     */
    Dict& assign(const std::string& __str, std::size_t __pos, std::size_t __n = std::string::npos) {
        getString().assign(__str, __pos, __n);
        return *this;
    }

    /**
     * @brief Set value to a C substring.
     * This function sets the value of this string to the first __n characters of __s.
     * If __n is is larger than the number of available characters in __s, the remainder of __s is used.
     *
     * @param __s The C string to use.
     * @param __n Number of characters to use.
     * @return Dict& Reference to this dictionnary.
     * @throw AccessException if type is not null or not a string.
     */
    Dict& assign(const char* __s, std::size_t __n) {
        getString().assign(__s, __n);
        return *this;
    }

    /**
     * @brief Set value to contents of a C string.
     * This function sets the value of this string to the value of __s.
     * The data is copied, so there is no dependence on __s once the function returns.
     *
     * @param __s The C string to use.
     * @return Dict& Reference to this dictionnary.
     * @throw AccessException if type is not null or not a string.
     */
    Dict& assign(const char* __s) {
        getString().assign(__s);
        return *this;
    }

    /**
     * @brief Set value to multiple characters.
     * This function sets the value of this string to __n copies of character __c.
     *
     * @param __n Length of the resulting string.
     * @param __c The character to use.
     * @return Dict& Reference to this dictionnary.
     * @throw AccessException if type is not null or not a string.
     */
    Dict& assign(std::size_t __n, char __c) {
        getString().assign(__n, __c);
        return *this;
    }

    /**
     * @brief Set value to a range of characters.
     * Sets value of string to characters in the range (__first,__last).
     *
     * @param __first Iterator referencing the first character to append.
     * @param __last Iterator marking the end of the range.
     * @throw AccessException if type is not null or not a string.
     */
    template<typename _InputIterator>
    void string_assign(_InputIterator __first, _InputIterator __last) {
        getString().assign(__first, __last);
    }

    /**
     * @brief Returns a read/write iterator that points to the first character in the %string.
     *
     * @throw AccessException if type is not null or not a string.
     */
    string_t::iterator string_begin() {
        return getString().begin();
    }

    /**
     * @brief Returns a read-only (constant) iterator that points to the first character in the %string.
     *
     * @throw AccessException if type is not a string.
     */
    string_t::const_iterator string_begin() const {
        return getString().begin();
    }

    /**
     * @brief Return const pointer to null-terminated contents.
     * This is a handle to internal data.
     * Do not modify or dire things may happen.
     *
     * @throw AccessException if dict type is not a string.
     */
    const char* c_str() const {
        return getString().c_str();
    }

    /**
     * @brief Compare to a string.
     * Determines the effective length rlen of the strings to compare as the smallest of size() and str.size().
     * The function then compares the two strings by calling traits::compare(data(), str.data(),rlen).
     * If the result of the comparison is nonzero returns it, otherwise the shorter one is ordered first.
     *
     * @param __str String to compare against.
     * @return int Integer < 0, 0, or > 0.
     * Returns an integer < 0 if this string is ordered before __str,
     * 0 if their values are equivalent,
     * or > 0 if this string is ordered after __str.
     * @throw AccessException if dict type is not a string.
     */
    int compare(const std::string& __str) const {
        return getString().compare(__str);
    }

    /**
     * @brief Compare substring to a string.
     * Determines the effective length rlen of the strings to compare as the smallest of the length of the substring and
     * __str.size(). The function then compares the two strings by calling
     * traits::compare(substring.data(),str.data(),rlen). If the result of the comparison is nonzero returns it,
     * otherwise the shorter one is ordered first.
     *
     * @param __pos Index of first character of substring.
     * @param __n Number of characters in substring.
     * @param __str String to compare against.
     * @return int Integer < 0, 0, or > 0.
     * Form the substring of this string from the __n characters starting at __pos.
     * Returns an integer < 0 if the substring is ordered before __str,
     * 0 if their values are equivalent,
     * or > 0 if the substring is ordered after * __str.
     * @throw AccessException if dict type is not a string.
     */
    int compare(std::size_t __pos, std::size_t __n, const std::string& __str) const {
        return getString().compare(__pos, __n, __str);
    }

    /**
     * @brief Compare substring to a substring.
     * Determines the effective length rlen of the strings to compare as the smallest of the lengths of the substrings.
     * The function then compares the two strings by calling
     * traits::compare(substring.data(),str.substr(pos2,n2).data(),rlen). If the result of the comparison is nonzero
     * returns it, otherwise the shorter one is ordered first.
     *
     * @param __pos1 Index of first character of substring.
     * @param __n1 Number of characters in substring.
     * @param __str String to compare against.
     * @param __pos2 Index of first character of substring of str.
     * @param __n2 Number of characters in substring of str.
     * @return int Integer < 0, 0, or > 0.
     * Form the substring of this string from the __n1 characters starting at __pos1.
     * Form the substring of * __str from the __n2 characters starting at __pos2.
     * Returns an integer < 0 if this substring is ordered before the substring of __str,
     * 0 if their values are equivalent,
     * or > 0 if this substring is ordered after the substring of __str.
     * @throw AccessException if dict type is not a string.
     */
    int compare(std::size_t __pos1, std::size_t __n1, const std::string& __str, std::size_t __pos2,
                std::size_t __n2 = std::string::npos) const {
        return getString().compare(__pos1, __n1, __str, __pos2, __n2);
    }

    /**
     * @brief Compare to a C string.
     * Determines the effective length rlen of the strings to compare as the smallest of size() and the length of a
     * string constructed from __s.
     * The function then compares the two strings by calling traits::compare(data(),s,rlen).
     * If the result of the comparison is nonzero returns it,
     * otherwise the shorter one is ordered first.
     *
     * @param __s C string to compare against.
     * @return int Integer < 0, 0, or > 0.
     * Returns an integer < 0 if this string is ordered before __s,
     * 0 if their values are equivalent, or > 0 if this string is ordered after __s.
     * @throw AccessException if dict type is not a string.
     */
    int compare(const char* __s) const {
        return getString().compare(__s);
    }

    /**
     * @brief Compare substring to a string.
     * Determines the effective length rlen of the strings to compare as the smallest of the length of the substring and
     * the length of a string constructed from @a __s.
     * The function then compares the two string by calling traits::compare(substring.data(),__s,rlen).
     * If the result of the comparison is nonzero returns it,
     * otherwise the shorter one is ordered first.
     *
     * @param __pos Index of first character of substring.
     * @param __n1 Number of characters in substring.
     * @param __s C string to compare against.
     * @return int Integer < 0, 0, or > 0.
     * Form the substring of this string from the @a __n1 characters starting at @a pos.
     * Returns an integer < 0 if the substring is ordered before @a __s,
     * 0 if their values are equivalent, or > 0 if the substring is ordered after @a __s.
     * @throw AccessException if dict type is not a string.
     */
    int compare(std::size_t __pos, std::size_t __n1, const char* __s) const {
        return getString().compare(__pos, __n1, __s);
    }

    /**
     * @brief Compare substring against a character %array.
     * Determines the effective length rlen of the strings to compare as the
     * smallest of the length of the substring and @a __n2.
     * The function then compares the two strings by calling traits::compare(substring.data(),s,rlen).
     * If the result of the comparison is nonzero returns it,
     * otherwise the shorter one is ordered first.
     *
     * NB: s must have at least n2 characters, &apos;\\0&apos; has
     * no special meaning.
     *
     * @param __pos Index of first character of substring.
     * @param __n1 Number of characters in substring.
     * @param __s character %array to compare against.
     * @param __n2 Number of characters of s.
     * @return int Integer < 0, 0, or > 0.
     * Form the substring of this string from the @a __n1 characters starting at @a __pos.
     * Form a string from the first @a __n2 characters of @a __s.
     * Returns an integer < 0 if this substring is ordered before the string from @a __s,
     * 0 if their values are equivalent, or > 0 if this substring is ordered after the string from @a __s.
     * @throw AccessException if dict type is not a string.
     */
    int compare(std::size_t __pos, std::size_t __n1, const char* __s, std::size_t __n2) const {
        return getString().compare(__pos, __n1, __s, __n2);
    }

    /**
     * @brief Copy substring into C string.
     * Copies up to @p __n characters starting at @p __pos into the C string @p __s.
     * If @p __pos is %greater than size(), out_of_range is thrown.
     *
     * @param __s C string to copy value into.
     * @param __n Number of characters to copy.
     * @param __pos Index of first character to copy.
     * @return std::size_t Number of characters actually copied.
     * @throw std::out_of_range If @p __pos > size().
     * @throw AccessException if dict type is not a string.
     */
    std::size_t copy(char* __s, std::size_t __n, std::size_t __pos = 0) const {
        return getString().copy(__s, __n, __pos);
    }

    /**
     * @brief Return const pointer to contents.
     * This is a pointer to internal data.
     * It is undefined to modify the contents through the returned pointer.
     * To get a pointer that allows modifying the contents use &str[0] instead.
     * @throw AccessException if dict type is not a string.
     */
    const char* data() const {
        return getString().data();
    }

    /**
     * @brief Return a read/write iterator that points one past the last character in the %string.
     *
     * @throw AccessException if dict type is not null or not a string.
     */
    string_t::iterator string_end() {
        return getString().end();
    }

    /**
     * @brief Return a read-only (constant) iterator that points one past the last character in the %string.
     *
     * @return string_t::const_iterator
     * @throw AccessException if dict type is not a string.
     */
    string_t::const_iterator string_end() const {
        return getString().end();
    }

    /**
     * @brief Remove characters.
     *
     * @param __pos Index of first character to remove (default 0).
     * @param __n Number of characters to remove (default remainder).
     * @return Dict& Reference to this dictionnary.
     * @throw AccessException if dict type is not null or not a string.
     */
    Dict& erase(std::size_t __pos = 0, std::size_t __n = std::string::npos) {
        getString().erase(__pos, __n);
        return *this;
    }

    /**
     * @brief Remove one character.
     * Removes the character at @p __position from this string.
     * The value of the string doesn't change if an error is thrown.
     *
     * @param __position Iterator referencing the character to remove.
     * @return string_t::iterator iterator referencing same location after removal.
     * @throw AccessException if dict type is not null or not a string.
     */
    string_t::iterator erase(string_t::iterator __position) {
        return getString().erase(__position);
    }

    /**
     * @brief Remove a range of characters.
     * Removes the characters in the range (first,last) from this string.
     * The value of the string doesn't change if an error is thrown.
     *
     * @param __first Iterator referencing the first character to remove.
     * @param __last Iterator referencing the end of the range.
     * @return string_t::iterator Iterator referencing location of first after removal.
     * @throw AccessException if dict type is not null or not a string.
     */
    string_t::iterator erase(string_t::iterator __first, string_t::iterator __last) {
        return getString().erase(__first, __last);
    }

    /**
     * @brief Find position of a C substring.
     * Starting from @p __pos,
     * searches forward for the first @p __n characters in @p __s within this string.
     * If found, returns the index where it begins.
     * If not found, returns npos.
     *
     * @param __s C string to locate.
     * @param __pos Index of character to search from.
     * @param __n Number of characters from s to search for.
     * @return std::size_t Index of start of first occurrence.
     * @throw AccessException if dict type is not a string.
     */
    std::size_t find(const char* __s, std::size_t __pos, std::size_t __n) const {
        return getString().find(__s, __pos, __n);
    }

    /**
     * @brief Find position of a string.
     * Starting from @p __pos,
     * searches forward for value of @p __str within this string.
     * If found, returns the index where it begins.
     * If not found, returns npos.
     *
     * @param __str String to locate.
     * @param __pos Index of character to search from (default 0).
     * @return std::size_t Index of start of first occurrence.
     * @throw AccessException if dict type is not a string.
     */
    std::size_t find(const string_t& __str, std::size_t __pos = 0) const {
        return getString().find(__str, __pos);
    }

    /**
     * @brief Find position of a string.
     * Starting from @p __pos,
     * searches forward for value of @p __str within this string.
     * If found, returns the index where it begins.
     * If not found, returns npos.
     *
     * @param __str C string to locate.
     * @param __pos Index of character to search from (default 0).
     * @return std::size_t Index of start of first occurrence.
     * @throw AccessException if dict type is not a string.
     */
    std::size_t find(const char* __str, std::size_t __pos = 0) const {
        return getString().find(__str, __pos);
    }

    /**
     * @brief Find position of a character.
     * Starting from @p __pos,
     * searches forward for @p __c within this string.
     * If found, returns the index where it was found.
     * If not found, returns npos.
     *
     * @param __c Character to locate.
     * @param __pos Index of character to search from (default 0).
     * @return std::size_t Index of first occurrence.
     * @throw AccessException if dict type is not a string.
     */
    std::size_t find(char __c, std::size_t __pos = 0) const {
        return getString().find(__c, __pos);
    }

    /**
     * @brief Find position of a character not in string.
     * Starting from @p __pos,
     * searches forward for a character not contained in @p __str within this string.
     * If found, returns the index where it was found.
     * If not found, returns npos.
     *
     * @param __str String containing characters to avoid.
     * @param __pos Index of character to search from (default 0).
     * @return std::size_t Index of first occurrence.
     * @throw AccessException if dict type is not a string.
     */
    std::size_t find_first_not_of(const string_t& __str, std::size_t __pos = 0) const {
        return getString().find_first_not_of(__str, __pos);
    }

    /**
     * @brief Find position of a character not in C substring.
     * Starting from @p __pos,
     * searches forward for a character not contained in the first @p __n characters of @p __s within this string.
     * If found, returns the index where it was found.
     * If not found, returns npos.
     *
     * @param __s C string containing characters to avoid.
     * @param __pos Index of character to search from.
     * @param __n Number of characters from __s to consider.
     * @return std::size_t Index of first occurrence.
     * @throw AccessException if dict type is not a string.
     */
    std::size_t find_first_not_of(const char* __s, std::size_t __pos, std::size_t __n) const {
        return getString().find_first_not_of(__s, __pos, __n);
    }

    /**
     * @brief Find position of a character not in C string.
     * Starting from @p __pos,
     * searches forward for a character not contained in @p __s within this string.
     * If found, returns the index where it was found.
     * If not found, returns npos.
     *
     * @param __s C string containing characters to avoid.
     * @param __pos Index of character to search from (default 0).
     * @return std::size_t Index of first occurrence.
     * @throw AccessException if dict type is not a string.
     */
    std::size_t find_first_not_of(const char* __s, std::size_t __pos = 0) const {
        return getString().find_first_not_of(__s, __pos);
    }

    /**
     * @brief Find position of a different character.
     * Starting from @p __pos,
     * searches forward for a character other than @p __c within this string.
     * If found, returns the index where it was found.
     * If not found, returns npos.
     *
     * @param __c Character to avoid.
     * @param __pos Index of character to search from (default 0).
     * @return std::size_t Index of first occurrence.
     * @throw AccessException if dict type is not a string.
     */
    std::size_t find_first_not_of(char __c, std::size_t __pos = 0) const {
        return getString().find_first_not_of(__c, __pos);
    }

    /**
     * @brief Find position of a character of string.
     * Starting from @p __pos,
     * searches forward for one of the characters of @p __str within this string.
     * If found, returns the index where it was found.
     * If not found, returns npos.
     *
     * @param __str String containing characters to locate.
     * @param __pos Index of character to search from (default 0).
     * @return std::size_t Index of first occurrence.
     * @throw AccessException if dict type is not a string.
     */
    std::size_t find_first_of(const string_t& __str, std::size_t __pos = 0) const {
        return getString().find_first_of(__str, __pos);
    }

    /**
     * @brief Find position of a character of C substring.
     * Starting from @p __pos,
     * searches forward for one of the first @p __n characters of @p __s within this string.
     * If found, returns the index where it was found.
     * If not found, returns npos.
     *
     * @param __s String containing characters to locate.
     * @param __pos Index of character to search from.
     * @param __n Number of characters from s to search for.
     * @return std::size_t Index of first occurrence.
     * @throw AccessException if dict type is not a string.
     */
    std::size_t find_first_of(const char* __s, std::size_t __pos, std::size_t __n) const {
        return getString().find_first_of(__s, __pos, __n);
    }

    /**
     * @brief Find position of a character of C string.
     * Starting from __pos,
     * searches forward for one of the characters of __s within this string.
     * If found, returns the index where it was found.
     * If not found, returns npos.
     *
     * @param __s String containing characters to locate.
     * @param __pos Index of character to search from (default 0).
     * @return std::size_t Index of first occurrence.
     * @throw AccessException if dict type is not a string.
     */
    std::size_t find_first_of(const char* __s, std::size_t __pos = 0) const {
        return getString().find_first_of(__s, __pos);
    }

    /**
     * @brief Find position of a character.
     * Starting from __pos,
     * searches forward for the character __c within this string.
     * If found, returns the index where it was found.
     * If not found, returns npos.
     * Note: equivalent to find(__c, __pos).
     *
     * @param __c Character to locate.
     * @param __pos Index of character to search from (default 0).
     * @return std::size_t Index of first occurrence.
     * @throw AccessException if dict type is not a string.
     */
    std::size_t find_first_of(char __c, std::size_t __pos = 0) const {
        return getString().find_first_of(__c, __pos);
    }

    /**
     * @brief Find last position of a character not in string.
     * Starting from __pos,
     * searches backward for a character not contained in __str within this string.
     * If found, returns the index where it was found.
     * If not found, returns npos.
     *
     * @param __str String containing characters to avoid.
     * @param __pos Index of character to search back from (default end).
     * @return std::size_t Index of last occurrence.
     * @throw AccessException if dict type is not a string.
     */
    std::size_t find_last_not_of(const string_t& __str, std::size_t __pos = std::string::npos) const {
        return getString().find_last_not_of(__str, __pos);
    }

    /**
     * @brief Find last position of a character not in C substring.
     * Starting from __pos,
     * searches backward for a character not contained in the first __n characters of __s within this string.
     * If found, returns the index where it was found.
     * If not found, returns npos.
     *
     * @param __s C string containing characters to avoid.
     * @param __pos Index of character to search back from.
     * @param __n Number of characters from s to consider.
     * @return std::size_t Index of last occurrence.
     * @throw AccessException if dict type is not a string.
     */
    std::size_t find_last_not_of(const char* __s, std::size_t __pos, std::size_t __n) const {
        return getString().find_last_not_of(__s, __pos, __n);
    }

    /**
     * @brief Find last position of a character not in C string.
     * Starting from __pos,
     * searches backward for a character not contained in __s within this string.
     * If found, returns the index where it was found.
     * If not found, returns npos.
     *
     * @param __s C string containing characters to avoid.
     * @param __pos Index of character to search back from (default end).
     * @return std::size_t Index of last occurrence.
     * @throw AccessException if dict type is not a string.
     */
    std::size_t find_last_not_of(const char* __s, std::size_t __pos = std::string::npos) const {
        return getString().find_last_not_of(__s, __pos);
    }

    /**
     * @brief Find last position of a different character.
     * Starting from __pos,
     * searches backward for a character other than __c within this string.
     * If found, returns the index where it was found.
     * If not found, returns npos.
     *
     * @param __c Character to avoid.
     * @param __pos Index of character to search back from (default end).
     * @return std::size_t Index of last occurrence.
     * @throw AccessException if dict type is not a string.
     */
    std::size_t find_last_not_of(char __c, std::size_t __pos = std::string::npos) const {
        return getString().find_last_not_of(__c, __pos);
    }

    /**
     * @brief Find last position of a character of string.
     * Starting from __pos,
     * searches backward for one of the characters of __str within this string.
     * If found, returns the index where it was found.
     * If not found, returns npos.
     *
     * @param __str String containing characters to locate.
     * @param __pos Index of character to search back from (default end).
     * @return std::size_t Index of last occurrence.
     * @throw AccessException if dict type is not a string.
     */
    std::size_t find_last_of(const string_t& __str, std::size_t __pos = std::string::npos) const {
        return getString().find_last_of(__str, __pos);
    }

    /**
     * @brief Find last position of a character of C substring.
     * Starting from __pos,
     * searches backward for one of the first __n characters of __s within this string.
     * If found, returns the index where it was found.
     * If not found, returns npos.
     *
     * @param __s C string containing characters to locate.
     * @param __pos Index of character to search back from.
     * @param __n Number of characters from s to search for.
     * @return std::size_t Index of last occurrence.
     * @throw AccessException if dict type is not a string.
     */
    std::size_t find_last_of(const char* __s, std::size_t __pos, std::size_t __n) const {
        return getString().find_last_of(__s, __pos, __n);
    }

    /**
     * @brief Find last position of a character of C string.
     * Starting from __pos,
     * searches backward for one of the characters of __s within this string.
     * If found, returns the index where it was found.
     * If not found, returns npos.
     *
     * @param __s C string containing characters to locate.
     * @param __pos Index of character to search back from (default end).
     * @return std::size_t Index of last occurrence.
     * @throw AccessException if dict type is not a string.
     */
    std::size_t find_last_of(const char* __s, std::size_t __pos = std::string::npos) const {
        return getString().find_last_of(__s, __pos);
    }

    /**
     * @brief Find last position of a character.
     * Starting from __pos,
     * searches backward for __c within this string.
     * If found, returns the index where it was found.
     * If not found, returns npos.
     * Note: equivalent to rfind(__c, __pos).
     *
     * @param __c Character to locate.
     * @param __pos Index of character to search back from (default end).
     * @return std::size_t Index of last occurrence.
     * @throw AccessException if dict type is not a string.
     */
    std::size_t find_last_of(char __c, std::size_t __pos = std::string::npos) const {
        return getString().find_last_of(__c, __pos);
    }

    /**
     * @brief Return copy of allocator used to construct this string.
     * @throw AccessException if dict type is not a string.
     */
    string_t::allocator_type string_get_allocator() const {
        return getString().get_allocator();
    }

    /**
     * @brief Insert multiple characters.
     * Inserts __n copies of character __c starting at the position referenced by iterator __p.
     * If adding characters causes the length to exceed max_size(), length_error is thrown.
     * The value of the string doesn't change if an error is thrown.
     *
     * @param __p Iterator referencing location in string to insert at.
     * @param __n Number of characters to insert.
     * @param __c The character to insert.
     * @throw std::length_error If new length exceeds max_size().
     * @throw AccessException if dict type is not null or not a string.
     */
    void insert(string_t::iterator __p, std::size_t __n, char __c) {
        getString().insert(__p, __n, __c);
    }

    /**
     * @brief  Insert a range of characters.
     * Inserts characters in range (__beg,__end).
     * If adding characters causes the length to exceed max_size(), length_error is thrown.
     * The value of the string doesn't change if an error is thrown.
     *
     * @param __p Iterator referencing location in string to insert at.
     * @param __beg Start of range.
     * @param __end End of range.
     * @throw std::length_error If new length exceeds @c max_size().
     * @throw AccessException if dict type is not null or not a string.
     */
    template<class _InputIterator>
    void insert(string_t::iterator __p, _InputIterator __beg, _InputIterator __end) {
        getString().insert(__p, __beg, __end);
    }

    /**
     * @brief Insert value of a string.
     * Inserts value of __str starting at __pos1.
     * If adding characters causes the length to exceed max_size(), length_error is thrown.
     * The value of the string doesn't change if an error is thrown.
     *
     * @param __pos1 Iterator referencing location in string to insert at.
     * @param __str The string to insert.
     * @return Dict& Reference to this dictionnary.
     * @throw std::length_error If new length exceeds max_size().
     * @throw AccessException if dict type is not null or not a string.
     */
    Dict& insert(std::size_t __pos1, const string_t& __str) {
        getString().insert(__pos1, __str);
        return *this;
    }

    /**
     * @brief Insert a substring.
     * Starting at pos1, insert __n character of __str beginning with __pos2.
     * If adding characters causes the length to exceed max_size(), length_error is thrown.
     * If __pos1 is beyond the end of this string or __pos2 is beyond the end of __str, out_of_range is thrown.
     * The value of the string doesn't change if an error is thrown.
     *
     * @param __pos1 Iterator referencing location in string to insert at.
     * @param __str The string to insert.
     * @param __pos2 Start of characters in str to insert.
     * @param __n Number of characters to insert.
     * @return Dict& Reference to this dictionnary.
     * @throw std::length_error If new length exceeds max_size().
     * @throw std::out_of_range If pos1 > size() or __pos2 > str.size().
     * @throw AccessException if dict type is not null or not a string.
     */
    Dict& insert(std::size_t __pos1, const string_t& __str, std::size_t __pos2, std::size_t __n = std::string::npos) {
        getString().insert(__pos1, __str, __pos2, __n);
        return *this;
    }

    /**
     * @brief Insert a C substring.
     * Inserts the first __n characters of __s starting at __pos.
     * If adding characters causes the length to exceed max_size(), length_error is thrown.
     * If __pos is beyond end(), out_of_range is thrown.
     * The value of the string doesn't change if an error is thrown.
     *
     * @param __pos Iterator referencing location in string to insert at.
     * @param __s The C string to insert.
     * @param __n The number of characters to insert.
     * @return Dict& Reference to this dictionnary.
     * @throw std::length_error If new length exceeds max_size().
     * @throw std::out_of_range If __pos is beyond the end of this string.
     * @throw AccessException if dict type is not null or not a string.
     */
    Dict& insert(std::size_t __pos, const char* __s, std::size_t __n) {
        getString().insert(__pos, __s, __n);
        return *this;
    }

    /**
     * @brief Insert a C string.
     * Inserts the first n characters of __s starting at __pos.
     * If adding characters causes the length to exceed max_size(), length_error is thrown.
     * If __pos is beyond end(), out_of_range is thrown.
     * The value of the string doesn't change if an error is thrown.
     *
     * @param __pos Iterator referencing location in string to insert at.
     * @param __s The C string to insert.
     * @return Dict& Reference to this dictionnary.
     * @throw std::length_error If new length exceeds max_size().
     * @throw std::out_of_range If pos is beyond the end of this string.
     * @throw AccessException if dict type is not null or not a string.
     */
    Dict& insert(std::size_t __pos, const char* __s) {
        getString().insert(__pos, __s);
        return *this;
    }

    /**
     * @brief Insert multiple characters.
     * Inserts __n copies of character __c starting at index __pos.
     * If adding characters causes the length to exceed max_size(), length_error is thrown.
     * If __pos > length(), out_of_range is thrown.
     * The value of the string doesn't change if an error is thrown.
     *
     * @param __pos Index in string to insert at.
     * @param __n Number of characters to insert.
     * @param __c The character to insert.
     * @return Dict& Reference to this dictionnary.
     * @throw std::length_error If new length exceeds max_size().
     * @throw std::out_of_range If __pos is beyond the end of this string.
     * @throw AccessException if dict type is not null or not a string.
     */
    Dict& insert(std::size_t __pos, std::size_t __n, char __c) {
        getString().insert(__pos, __n, __c);
        return *this;
    }

    /**
     * @brief Insert one character.
     * Inserts character __c at position referenced by __p.
     * If adding character causes the length to exceed max_size(), length_error is thrown.
     * If __p is beyond end of string, out_of_range is thrown.
     * The value of the string doesn't change if an error is thrown.
     *
     * @param __p Iterator referencing position in string to insert at.
     * @param __c The character to insert.
     * @return string_t::iterator Iterator referencing newly inserted char.
     * @throw std::length_error If new length exceeds max_size()
     * @throw AccessException if dict type is not null or not a string.
     */
    string_t::iterator insert(string_t::iterator __p, char __c) {
        return getString().insert(__p, __c);
    }

    /**
     * @return std::size_t number of characters in the string, not including any null-termination.
     * @throw AccessException if dict type is not a string.
     */
    std::size_t length() const {
        return getString().length();
    }

    /**
     * @brief Append a string to this string.
     *
     * @param __str The string to append.
     * @return Dict& Reference to this dictionnary.
     * @throw AccessException if dict type is not null or not a string.
     */
    Dict& operator+=(const string_t& __str) {
        getString().operator+=(__str);
        return *this;
    }

    /**
     * @brief Append a C string.
     *
     * @param __s The C string to append.
     * @return Dict& Reference to this dictionnary.
     * @throw AccessException if dict type is not null or not a string.
     */
    Dict& operator+=(const char* __s) {
        getString().operator+=(__s);
        return *this;
    }

    /**
     * @brief Append a character.
     *
     * @param __c The character to append.
     * @return Dict& Reference to this dictionnary.
     * @throw AccessException if dict type is not null or not a string.
     */
    Dict& operator+=(char __c) {
        getString().operator+=(__c);
        return *this;
    }

    /**
     * @brief Append a single character.
     *
     * @param __c Character to append.
     * @throw AccessException if dict type is not null or not a string.
     */
    void string_push_back(char __c) {
        getString().push_back(__c);
    }

    /**
     * @brief Returns a read/write reverse iterator that points to the last character in the %string.
     * Iteration is done in reverse element order.
     * @throw AccessException if dict type is not null or not a string.
     */
    string_t::reverse_iterator string_rbegin() {
        return getString().rbegin();
    }

    /**
     * @brief Returns a read-only (constant) reverse iterator that points to the last character in the %string.
     * Iteration is done in reverse element order.
     * @throw AccessException if dict type is not a string.
     */
    string_t::const_reverse_iterator string_rbegin() const {
        return getString().rbegin();
    }

    /**
     * @brief Returns a read/write reverse iterator that points to one before the first character in the %string.
     * Iteration is done in reverse element order.
     * @throw AccessException if dict type is not null or not a string.
     */
    string_t::reverse_iterator string_rend() {
        return getString().rend();
    }

    /**
     * @brief Returns a read-only (constant) reverse iterator that points
     * to one before the first character in the %string.
     * Iteration is done in reverse element order.
     * @throw AccessException if dict type is not a string.
     */
    string_t::const_reverse_iterator string_rend() const {
        return getString().rend();
    }

    /**
     * @brief Replace characters with value from another string.
     * Removes the characters in the range (__pos,__pos+__n) from this string.
     * In place, the value of __str is inserted.
     * If __pos is beyond end of string, out_of_range is thrown.
     * If the length of the result exceeds max_size(), length_error is thrown.
     * The value of the string doesn't change if an error is thrown.
     *
     * @param __pos Index of first character to replace.
     * @param __n Number of characters to be replaced.
     * @param __str String to insert.
     * @return Dict& Reference to this dictionnary.
     * @throw std::out_of_range If pos is beyond the end of this string.
     * @throw std::length_error If new length exceeds max_size().
     * @throw AccessException if dict type is not null or not a string.
     */
    Dict& replace(std::size_t __pos, std::size_t __n, const string_t& __str) {
        getString().replace(__pos, __n, __str);
        return *this;
    }

    /**
     * @brief Replace characters with value from another string.
     * Removes the characters in the range (__pos1,__pos1 + n) from this string.
     * In place, the value of __str is inserted.
     * If __pos is beyond end of string, out_of_range is thrown.
     * If the length of the result exceeds max_size(), length_error is thrown.
     * The value of the string doesn't change if an error is thrown.
     *
     * @param __pos1 Index of first character to replace.
     * @param __n1 Number of characters to be replaced.
     * @param __str String to insert.
     * @param __pos2 Index of first character of str to use.
     * @param __n2 Number of characters from str to use.
     * @return Dict& Reference to this dictionnary.
     * @throw std::out_of_range If __pos1 > size() or __pos2 > __str.size().
     * @throw std::length_error If new length exceeds max_size().
     * @throw AccessException if dict type is not null or not a string.
     */
    Dict& replace(std::size_t __pos1, std::size_t __n1, const string_t& __str, std::size_t __pos2,
                  std::size_t __n2 = std::string::npos) {
        getString().replace(__pos1, __n1, __str, __pos2, __n2);
        return *this;
    }

    /**
     * @brief Replace characters with value of a C substring.
     * Removes the characters in the range (__pos,__pos + __n1) from this string.
     * In place, the first __n2 characters of __s are inserted, or all of __s if __n2 is too large.
     * If __pos is beyond end of string, out_of_range is thrown.
     * If the length of result exceeds max_size(), length_error is thrown.
     * The value of the string doesn't change if an error is thrown.
     *
     * @param __pos Index of first character to replace.
     * @param __n1 Number of characters to be replaced.
     * @param __s C string to insert.
     * @param __n2 Number of characters from s to use.
     * @return Dict& Reference to this dictionnary.
     * @throw std::out_of_range If pos1 > size().
     * @throw std::length_error If new length exceeds max_size().
     * @throw AccessException if dict type is not null or not a string.
     */
    Dict& replace(std::size_t __pos, std::size_t __n1, const char* __s, std::size_t __n2) {
        getString().replace(__pos, __n1, __s, __n2);
        return *this;
    }

    /**
     * @brief Replace characters with value of a C string.
     * Removes the characters in the range (__pos,__pos + __n1) from this string.
     * In place, the characters of __s are inserted.
     * If __pos is beyond end of string, out_of_range is thrown.
     * If the length of result exceeds max_size(), length_error is thrown.
     * The value of the string doesn't change if an error is thrown.
     *
     * @param __pos Index of first character to replace.
     * @param __n1 Number of characters to be replaced.
     * @param __s C string to insert.
     * @return Dict& Reference to this dictionnary.
     * @throw std::out_of_range If pos1 > size().
     * @throw std::length_error If new length exceeds max_size().
     * @throw AccessException if dict type is not null or not a string.
     */
    Dict& replace(std::size_t __pos, std::size_t __n1, const char* __s) {
        getString().replace(__pos, __n1, __s);
        return *this;
    }

    /**
     * @brief Replace characters with multiple characters.
     * Removes the characters in the range (pos,pos + n1) from this string.
     * In place, __n2 copies of __c are inserted.
     * If __pos is beyond end of string, out_of_range is thrown.
     * If the length of result exceeds max_size(), length_error is thrown.
     * The value of the string doesn't change if an error is thrown.
     *
     * @param __pos Index of first character to replace.
     * @param __n1 Number of characters to be replaced.
     * @param __n2 Number of characters to insert.
     * @param __c Character to insert.
     * @return Dict& Reference to this dictionnary.
     * @throw std::out_of_range If pos1 > size().
     * @throw std::length_error If new length exceeds max_size().
     * @throw AccessException if dict type is not null or not a string.
     */
    Dict& replace(std::size_t __pos, std::size_t __n1, std::size_t __n2, char __c) {
        getString().replace(__pos, __n1, __n2, __c);
        return *this;
    }

    /**
     * @brief Replace range of characters with string.
     * Removes the characters in the range (__i1,__i2).
     * In place, the value of __str is inserted.
     * If the length of result exceeds max_size(), length_error is thrown.
     * The value of the string doesn't change if an error is thrown.
     *
     * @param __i1 Iterator referencing start of range to replace.
     * @param __i2 Iterator referencing end of range to replace.
     * @param __str String value to insert.
     * @return Dict& Reference to this dictionnary.
     * @throw std::length_error If new length exceeds max_size().
     * @throw AccessException if dict type is not null or not a string.
     */
    Dict& replace(string_t::iterator __i1, string_t::iterator __i2, const string_t& __str) {
        getString().replace(__i1, __i2, __str);
        return *this;
    }

    /**
     * @brief Replace range of characters with C substring.
     * Removes the characters in the range (__i1,__i2).
     * In place, the first __n characters of __s are inserted.
     * If the length of result exceeds max_size(), length_error is thrown.
     * The value of the string doesn't change if an error is thrown
     *
     * @param __i1 Iterator referencing start of range to replace.
     * @param __i2 Iterator referencing end of range to replace.
     * @param __s C string value to insert.
     * @param __n Number of characters from s to insert.
     * @return Dict& Reference to this dictionnary.
     * @throw std::length_error If new length exceeds max_size().
     * @throw AccessException if dict type is not null or not a string.
     */
    Dict& replace(string_t::iterator __i1, string_t::iterator __i2, const char* __s, std::size_t __n) {
        getString().replace(__i1, __i2, __s, __n);
        return *this;
    }

    /**
     * @brief Replace range of characters with C string.
     * Removes the characters in the range (__i1,__i2).
     * In place, the characters of __s are inserted.
     * If the length of result exceeds max_size(), length_error is thrown.
     * The value of the string doesn't change if an error is thrown.
     *
     * @param __i1 Iterator referencing start of range to replace.
     * @param __i2 Iterator referencing end of range to replace.
     * @param __s C string value to insert.
     * @return Dict& Reference to this dictionnary.
     * @throw std::length_error If new length exceeds max_size().
     * @throw AccessException if dict type is not null or not a string.
     */
    Dict& replace(string_t::iterator __i1, string_t::iterator __i2, const char* __s) {
        getString().replace(__i1, __i2, __s);
        return *this;
    }

    /**
     * @brief Replace range of characters with multiple characters
     * Removes the characters in the range (__i1,__i2).
     * In place, __n copies of __c are inserted.
     * If the length of result exceeds max_size(), length_error is thrown.
     * The value of the string doesn't change if an error is thrown.
     *
     * @param __i1 Iterator referencing start of range to replace.
     * @param __i2 Iterator referencing end of range to replace.
     * @param __n Number of characters to insert.
     * @param __c Character to insert.
     * @return Dict& Reference to this dictionnary.
     * @throw std::length_error If new length exceeds max_size().
     * @throw AccessException if dict type is not null or not a string.
     */
    Dict& replace(string_t::iterator __i1, string_t::iterator __i2, std::size_t __n, char __c) {
        getString().replace(__i1, __i2, __n, __c);
        return *this;
    }

    /**
     * @brief Replace range of characters with range.
     * Removes the characters in the range (__i1,__i2).
     * In place, characters in the range [__k1,__k2) are inserted.
     * If the length of result exceeds max_size(), length_error is thrown.
     * The value of the string doesn't change if an error is thrown.
     *
     * @tparam _InputIterator
     * @param __i1 Iterator referencing start of range to replace.
     * @param __i2 Iterator referencing end of range to replace.
     * @param __k1 Iterator referencing start of range to insert.
     * @param __k2 Iterator referencing end of range to insert.
     * @return Dict& Reference to this dictionnary.
     * @throw std::length_error If new length exceeds max_size().
     * @throw AccessException if dict type is not null or not a string.
     */
    template<class _InputIterator>
    Dict& replace(string_t::iterator __i1, string_t::iterator __i2, _InputIterator __k1, _InputIterator __k2) {
        getString().replace(__i1, __i2, __k1, __k2);
        return *this;
    }

    /**
     * @brief Replace range of characters with range.
     * Removes the characters in the range (__i1,__i2).
     * In place, characters in the range [__k1,__k2) are inserted.
     * If the length of result exceeds max_size(), length_error is thrown.
     * The value of the string doesn't change if an error is thrown.
     *
     * @param __i1 Iterator referencing start of range to replace.
     * @param __i2 Iterator referencing end of range to replace.
     * @param __k1 Pointer start of range to insert.
     * @param __k2 Pointer end of range to insert.
     * @return Dict& Reference to this dictionnary.
     * @throw std::length_error If new length exceeds max_size().
     * @throw AccessException if dict type is not null or not a string.
     */
    Dict& replace(string_t::iterator __i1, string_t::iterator __i2, char* __k1, char* __k2) {
        getString().replace(__i1, __i2, __k1, __k2);
        return *this;
    }

    /**
     * @brief Replace range of characters with range.
     * Removes the characters in the range (__i1,__i2).
     * In place, characters in the range [__k1,__k2) are inserted.
     * If the length of result exceeds max_size(), length_error is thrown.
     * The value of the string doesn't change if an error is thrown.
     *
     * @param __i1 Iterator referencing start of range to replace.
     * @param __i2 Iterator referencing end of range to replace.
     * @param __k1 Const pointer start of range to insert.
     * @param __k2 Const pointer end of range to insert.
     * @return Dict& Reference to this dictionnary.
     * @throw std::length_error If new length exceeds max_size().
     * @throw AccessException if dict type is not null or not a string.
     */
    Dict& replace(string_t::iterator __i1, string_t::iterator __i2, const char* __k1, const char* __k2) {
        getString().replace(__i1, __i2, __k1, __k2);
        return *this;
    }

    /**
     * @brief Replace range of characters with range.
     * Removes the characters in the range (__i1,__i2).
     * In place, characters in the range [__k1,__k2) are inserted.
     * If the length of result exceeds max_size(), length_error is thrown.
     * The value of the string doesn't change if an error is thrown.
     *
     * @param __i1 Iterator referencing start of range to replace.
     * @param __i2 Iterator referencing end of range to replace.
     * @param __k1 Iterator referencing start of range to insert.
     * @param __k2 Iterator referencing end of range to insert.
     * @return Dict& Reference to this dictionnary.
     * @throw std::length_error If new length exceeds max_size().
     * @throw AccessException if dict type is not null or not a string.
     */
    Dict& replace(string_t::iterator __i1, string_t::iterator __i2, string_t::iterator __k1, string_t::iterator __k2) {
        getString().replace(__i1, __i2, __k1, __k2);
        return *this;
    }

    /**
     * @brief Replace range of characters with range.
     * Removes the characters in the range (__i1,__i2).
     * In place, characters in the range [__k1,__k2) are inserted.
     * If the length of result exceeds max_size(), length_error is thrown.
     * The value of the string doesn't change if an error is thrown.
     *
     * @param __i1 Iterator referencing start of range to replace.
     * @param __i2 Iterator referencing end of range to replace.
     * @param __k1 Const iterator referencing start of range to insert.
     * @param __k2 Const iIterator referencing end of range to insert.
     * @return Dict& Reference to this dictionnary.
     * @throw std::length_error If new length exceeds max_size().
     * @throw AccessException if dict type is not null or not a string.
     */
    Dict& replace(string_t::iterator __i1, string_t::iterator __i2, string_t::const_iterator __k1,
                  string_t::const_iterator __k2) {
        getString().replace(__i1, __i2, __k1, __k2);
        return *this;
    }

    /**
     * @brief Resizes the %list to the specified number of elements.
     * This function will %resize the %list to the specified number of elements.
     * If the number is smaller than the %list's current size the %list is truncated,
     * otherwise the %list is extended and new elements are populated with given data.
     *
     * @param __n Number of elements the %list should contain.
     * @param __c Data with which new elements should be populated.
     * @throw AccessException if dict type is not null or not a string.
     */
    void resize(std::size_t __n, char __c) {
        getString().resize(__n, __c);
    }

    /**
     * @brief Find last position of a string.
     * Starting from __pos, searches backward for value of * __str within this string.
     * If found, returns the index where it begins.
     * If not found, returns npos.
     *
     * @param __str String to locate.
     * @param __pos Index of character to search back from (default end).
     * @return std::size_t Index of start of last occurrence.
     * @throw AccessException if dict type is not a string.
     */
    std::size_t rfind(const string_t& __str, std::size_t __pos = std::string::npos) const {
        return getString().rfind(__str, __pos);
    }

    /**
     * @brief Find last position of a C substring.
     * Starting from __pos, searches backward for the first * __n characters in __s within this string.
     * If found, returns the index where it begins.
     * If not found, returns npos.
     *
     * @param __s C string to locate.
     * @param __pos Index of character to search back from.
     * @param __n Number of characters from s to search for.
     * @return std::size_t Index of start of last occurrence.
     * @throw AccessException if dict type is not a string.
     */
    std::size_t rfind(const char* __s, std::size_t __pos, std::size_t __n) const {
        return getString().rfind(__s, __pos, __n);
    }

    /**
     * @brief Find last position of a C string.
     * Starting from __pos, searches backward for the value of __s within this string.
     * If found, returns the index where it begins.
     * If not found, returns npos.
     *
     * @param __s C string to locate.
     * @param __pos Index of character to start search at (default end).
     * @return std::size_t Index of start of last occurrence.
     * @throw AccessException if dict type is not a string.
     */
    std::size_t rfind(const char* __s, std::size_t __pos = std::string::npos) const {
        return getString().rfind(__s, __pos);
    }

    /**
     * @brief Find last position of a character.
     * Starting from __pos, searches backward for __c within this string.
     * If found, returns the index where it was found.
     * If not found, returns npos.
     *
     * @param __c Character to locate.
     * @param __pos Index of character to search back from (default end).
     * @return std::size_t Index of last occurrence.
     * @throw AccessException if dict type is not a string.
     */
    std::size_t rfind(char __c, std::size_t __pos = std::string::npos) const {
        return getString().rfind(__c, __pos);
    }

    /**
     * @brief Get a substring.
     * Construct and return a new string using the __n characters starting at __pos.
     * If the string is too short, use the remainder of the characters.
     * If __pos is beyond the end of the string, out_of_range is thrown.
     *
     * @param __pos Index of first character (default 0).
     * @param __n Number of characters in substring (default remainder).
     * @return string_t The new string.
     * @throw std::out_of_range If __pos > size().
     * @throw AccessException if dict type is not a string.
     */
    string_t substr(std::size_t __pos = 0, std::size_t __n = std::string::npos) const {
        return getString().substr(__pos, __n);
    }

    /**
     * @brief String equality comparison.
     *
     * @param value A string.
     * @return True if the value and the dict are equal.
     */
    bool operator==(const std::string& value) const {
        bool ret;
        switch (_type) {
            case NULL_TYPE:
            case NUMBER_TYPE:
            case ARRAY_TYPE:
            case BOOLEAN_TYPE:
            case OBJECT_TYPE:
                ret = false;
                break;
            case STRING_TYPE:
                ret = _value.getString() == value;
                break;
        }
        return ret;
    }

    /**
     * @brief C String equality comparison.
     *
     * @param value A C string.
     * @return True if the value and the dict are equal.
     */
    bool operator==(const char* value) const {
        bool ret;
        switch (_type) {
            case NULL_TYPE:
            case NUMBER_TYPE:
            case ARRAY_TYPE:
            case BOOLEAN_TYPE:
            case OBJECT_TYPE:
                ret = false;
                break;
            case STRING_TYPE:
                ret = _value.getString() == value;
                break;
        }
        return ret;
    }

    /**
     * @brief String equality comparison.
     *
     * @tparam Size Length of value.
     * @param value A string.
     * @return True if the value and the dict are equal.
     */
    template<std::size_t Size>
    bool operator==(const char (&value)[Size]) const {
        bool ret;
        switch (_type) {
            case NULL_TYPE:
            case NUMBER_TYPE:
            case ARRAY_TYPE:
            case BOOLEAN_TYPE:
            case OBJECT_TYPE:
                ret = false;
                break;
            case STRING_TYPE:
                ret = _value.getString() == value;
                break;
        }
        return ret;
    }

    /**
     * @brief String not equality comparison.
     *
     * @param value A string.
     * @return True if the value and the dict are not equal.
     */
    bool operator!=(const std::string& value) const {
        return !(operator==(value));
    }

    /**
     * @brief C String not equality comparison.
     *
     * @param value A C string.
     * @return True if the value and the dict are not equal.
     */
    bool operator!=(const char* value) const {
        return !(operator==(value));
    }

    /**
     * @brief String not equality comparison.
     *
     * @tparam Size Length of value.
     * @param value A string.
     * @return True if the value and the dict are not equal.
     */
    template<std::size_t Size>
    bool operator!=(const char (&value)[Size]) const {
        return !(operator==(value));
    }

    /**
     * @brief String ordering relation.
     *
     * @param value A string.
     * @return True if dict is string and is lexicographically greater than value.
     */
    bool operator>(const std::string& value) const {
        bool ret;
        switch (_type) {
            case NULL_TYPE:
            case NUMBER_TYPE:
            case ARRAY_TYPE:
            case BOOLEAN_TYPE:
            case OBJECT_TYPE:
                ret = false;
                break;
            case STRING_TYPE:
                ret = _value.getString() > value;
                break;
        }
        return ret;
    }

    /**
     * @brief C String ordering relation.
     *
     * @param value A C string.
     * @return True if dict is string and is lexicographically greater than value.
     */
    bool operator>(const char* value) const {
        bool ret;
        switch (_type) {
            case NULL_TYPE:
            case NUMBER_TYPE:
            case ARRAY_TYPE:
            case BOOLEAN_TYPE:
            case OBJECT_TYPE:
                ret = false;
                break;
            case STRING_TYPE:
                ret = _value.getString() > value;
                break;
        }
        return ret;
    }

    /**
     * @brief String ordering relation.
     *
     * @tparam Size Length of value.
     * @param value A string.
     * @return True if dict is string and is lexicographically greater than value.
     */
    template<std::size_t Size>
    bool operator>(const char (&value)[Size]) const {
        bool ret;
        switch (_type) {
            case NULL_TYPE:
            case NUMBER_TYPE:
            case ARRAY_TYPE:
            case BOOLEAN_TYPE:
            case OBJECT_TYPE:
                ret = false;
                break;
            case STRING_TYPE:
                ret = _value.getString() > value;
                break;
        }
        return ret;
    }

    /**
     * @brief String ordering relation.
     *
     * @param value A string.
     * @return True if dict is string and is lexicographically less than value.
     */
    bool operator<(const std::string& value) const {
        bool ret;
        switch (_type) {
            case NULL_TYPE:
            case NUMBER_TYPE:
            case ARRAY_TYPE:
            case BOOLEAN_TYPE:
            case OBJECT_TYPE:
                ret = false;
                break;
            case STRING_TYPE:
                ret = _value.getString() < value;
                break;
        }
        return ret;
    }

    /**
     * @brief C String ordering relation.
     *
     * @param value A C string.
     * @return True if dict is string and is lexicographically less than value.
     */
    bool operator<(const char* value) const {
        bool ret;
        switch (_type) {
            case NULL_TYPE:
            case NUMBER_TYPE:
            case ARRAY_TYPE:
            case BOOLEAN_TYPE:
            case OBJECT_TYPE:
                ret = false;
                break;
            case STRING_TYPE:
                ret = _value.getString() < value;
                break;
        }
        return ret;
    }

    /**
     * @brief String ordering relation.
     *
     * @tparam Size Length of value.
     * @param value A string.
     * @return True if dict is string and is lexicographically less than value.
     */
    template<std::size_t Size>
    bool operator<(const char (&value)[Size]) const {
        bool ret;
        switch (_type) {
            case NULL_TYPE:
            case NUMBER_TYPE:
            case ARRAY_TYPE:
            case BOOLEAN_TYPE:
            case OBJECT_TYPE:
                ret = false;
                break;
            case STRING_TYPE:
                ret = _value.getString() < value;
                break;
        }
        return ret;
    }

    /**
     * @brief String ordering relation.
     *
     * @param value A string.
     * @return True if dict is string and is lexicographically greater or equal than value.
     */
    bool operator>=(const std::string& value) const {
        bool ret;
        switch (_type) {
            case NULL_TYPE:
            case NUMBER_TYPE:
            case ARRAY_TYPE:
            case BOOLEAN_TYPE:
            case OBJECT_TYPE:
                ret = false;
                break;
            case STRING_TYPE:
                ret = _value.getString() >= value;
                break;
        }
        return ret;
    }

    /**
     * @brief C String ordering relation.
     *
     * @param value A C string.
     * @return True if dict is string and is lexicographically greater or equal than value.
     */
    bool operator>=(const char* value) const {
        bool ret;
        switch (_type) {
            case NULL_TYPE:
            case NUMBER_TYPE:
            case ARRAY_TYPE:
            case BOOLEAN_TYPE:
            case OBJECT_TYPE:
                ret = false;
                break;
            case STRING_TYPE:
                ret = _value.getString() >= value;
                break;
        }
        return ret;
    }

    /**
     * @brief String ordering relation.
     *
     * @tparam Size Length of value.
     * @param value A string.
     * @return True if dict is string and is lexicographically greater or equal than value.
     */
    template<std::size_t Size>
    bool operator>=(const char (&value)[Size]) const {
        bool ret;
        switch (_type) {
            case NULL_TYPE:
            case NUMBER_TYPE:
            case ARRAY_TYPE:
            case BOOLEAN_TYPE:
            case OBJECT_TYPE:
                ret = false;
                break;
            case STRING_TYPE:
                ret = _value.getString() >= value;
                break;
        }
        return ret;
    }

    /**
     * @brief String ordering relation.
     *
     * @param value A string.
     * @return True if dict is string and is lexicographically less or equal than value.
     */
    bool operator<=(const std::string& value) const {
        bool ret;
        switch (_type) {
            case NULL_TYPE:
            case NUMBER_TYPE:
            case ARRAY_TYPE:
            case BOOLEAN_TYPE:
            case OBJECT_TYPE:
                ret = false;
                break;
            case STRING_TYPE:
                ret = _value.getString() <= value;
                break;
        }
        return ret;
    }

    /**
     * @brief C String ordering relation.
     *
     * @param value A C string.
     * @return True if dict is string and is lexicographically less or equal than value.
     */
    bool operator<=(const char* value) const {
        bool ret;
        switch (_type) {
            case NULL_TYPE:
            case NUMBER_TYPE:
            case ARRAY_TYPE:
            case BOOLEAN_TYPE:
            case OBJECT_TYPE:
                ret = false;
                break;
            case STRING_TYPE:
                ret = _value.getString() <= value;
                break;
        }
        return ret;
    }

    /**
     * @brief String ordering relation.
     *
     * @tparam Size Length of value.
     * @param value A string.
     * @return True if dict is string and is lexicographically less or equal than value.
     */
    template<std::size_t Size>
    bool operator<=(const char (&value)[Size]) const {
        bool ret;
        switch (_type) {
            case NULL_TYPE:
            case NUMBER_TYPE:
            case ARRAY_TYPE:
            case BOOLEAN_TYPE:
            case OBJECT_TYPE:
                ret = false;
                break;
            case STRING_TYPE:
                ret = _value.getString() <= value;
                break;
        }
        return ret;
    }

    // -------------------------------------------------------------------------
    //  ........................................
    //  ..%%%%...%%%%%...%%%%%....%%%%...%%..%%.
    //  .%%..%%..%%..%%..%%..%%..%%..%%...%%%%..
    //  .%%%%%%..%%%%%...%%%%%...%%%%%%....%%...
    //  .%%..%%..%%..%%..%%..%%..%%..%%....%%...
    //  .%%..%%..%%..%%..%%..%%..%%..%%....%%...
    //  ........................................
    // -------------------------------------------------------------------------

    /**
     * @brief check if type of jsonator is a array
     *
     * @return true if type is a array else false
     */
    bool isArray() const {
        return _type == ARRAY_TYPE;
    }

    /**
     * @brief get the array of dict object
     *
     * @return array_t&
     * @throw AccessException if dict type is not a array
     */
    array_t& getArray() {
        if (!isNull() && !isArray()) {
            throw AccessException(*this, "is not a array");
        }
        if (isNull()) {
            _type = ARRAY_TYPE;
            _value.newArray();
        }
        return _value.getArray();
    }

    /**
     * @brief get the array of dict object
     *
     * @return const array_t&
     * @throw AccessException if dict type is not a array
     */
    const array_t& getArray() const {
        if (!isArray()) {
            throw AccessException(*this, "is not a array");
        }
        return _value.getArray();
    }

    /**
     * @brief set value from deque
     *
     * @tparam T
     * @param value
     * @throw AccessException if type is not null or not a array
     */
    template<typename T>
    Dict& operator=(const std::deque<T>& value) {
        newArray();
        typename std::deque<T>::const_iterator it;
        for (it = value.begin(); it != value.end(); ++it) {
            _value.getArray().push_back(*it);
        }
        return *this;
    }

    /**
     * @brief set value from list
     *
     * @tparam T
     * @param value
     * @throw AccessException if type is not null or not a array
     */
    template<typename T>
    Dict& operator=(const std::list<T>& value) {
        newArray();
        typename std::list<T>::const_iterator it;
        for (it = value.begin(); it != value.end(); ++it) {
            _value.getArray().push_back(*it);
        }
        return *this;
    }

    /**
     * @brief set value from map
     *
     * @tparam T key
     * @tparam U value
     * @param value
     * @throw AccessException if type is not null or not a array or not a object
     */
    template<typename T, typename U>
    Dict& operator=(const std::map<T, U>& value) {
        newArray();
        typename std::map<T, U>::const_iterator it;
        for (it = value.begin(); it != value.end(); ++it) {
            operator[](it->first) = it->second;
        }
        return *this;
    }

    /**
     * @brief set value from queue
     *
     * @tparam T
     * @param value
     * @throw AccessException if type is not null or not a array
     */
    template<typename T>
    Dict& operator=(const std::queue<T>& value) {
        newArray();
        std::queue<T> copy = value;
        while (!copy.empty()) {
            _value.getArray().push_back(copy.front());
            copy.pop();
        }
        return *this;
    }

    /**
     * @brief set value from set
     *
     * @tparam T
     * @param value
     * @throw AccessException if type is not null or not a array
     */
    template<typename T>
    Dict& operator=(const std::set<T>& value) {
        newArray();
        typename std::set<T>::const_iterator it;
        for (it = value.begin(); it != value.end(); ++it) {
            _value.getArray().push_back(*it);
        }
        return *this;
    }

    /**
     * @brief set value from stack
     *
     * @tparam T
     * @param value
     * @throw AccessException if type is not null or not a array
     */
    template<typename T>
    Dict& operator=(const std::stack<T>& value) {
        newArray();
        std::stack<T> copy = value;
        while (!copy.empty()) {
            _value.getArray().push_back(copy.top());
            copy.pop();
        }
        return *this;
    }

    /**
     * @brief set value from vector
     *
     * @tparam T
     * @param value
     * @throw AccessException if type is not null or not a array
     */
    template<typename T>
    Dict& operator=(const std::vector<T>& value) {
        newArray();
        typename std::vector<T>::const_iterator it;
        for (it = value.begin(); it != value.end(); ++it) {
            _value.getArray().push_back(*it);
        }
        return *this;
    }

    /**
     * @brief create array
     *
     * @throw AccessException if type is not a null and not a array
     */
    void newArray() {
        if (!isNull() && !isArray()) {
            throw AccessException(*this, "is not a array");
        }
        if (isNull()) {
            _type = ARRAY_TYPE;
            _value.newArray();
        }
    }

    /**
     * @brief get dict from @p index if the lowers indexies not exists create of null object
     *
     * @param index
     * @return Dict& data associated with the index or if the index does not exist,
     * a dict object with that index is created using default values, which is then returned
     * @throw AccessException if type is not a null and not a array
     */
    template<typename T>
    Dict& operator[](const T& index) {
        newArray();
        if (static_cast<std::size_t>(index) < _value.getArray().size()) {
            return _value.getArray()[static_cast<std::size_t>(index)];
        }
        while (_value.getArray().size() < static_cast<std::size_t>(index)) {
            _value.getArray().push_back(Dict());
        }
        _value.getArray().push_back(Dict());
        return _value.getArray().back();
    }

    /**
     * @brief get const dict from @p index
     *
     * @param index
     * @return const Dict&
     * @throw AccessException if type is not a array
     * @throw ChildException if index is not exists
     */
    template<typename T>
    const Dict& operator[](const T& index) const {
        if (!isArray()) {
            throw AccessException(*this, "is not a array");
        }
        if (static_cast<std::size_t>(index) < _value.getArray().size()) {
            return _value.getArray()[static_cast<std::size_t>(index)];
        }
        throw ChildException(*this, static_cast<unsigned long>(index));
    }

    /**
     * @brief check if array contains a @p index
     *
     * @param index
     * @return true if array has index else false
     * @throw AccessException if type is not a array
     */
    template<typename T>
    bool contains(const T& index) const {
        if (!isArray()) {
            throw AccessException(*this, "is not a array");
        }
        return static_cast<std::size_t>(index) < _value.getArray().size();
    }

    /**
     * @brief Assigns a given value to a %vector.
     * This function fills a %vector with __n copies of the given value.
     * Note that the assignment completely changes the %vector and
     * that the resulting %vector's size is the same as the number of elements assigned.
     *
     * @param __n Number of elements to be assigned.
     * @param __val Value to be assigned.
     * @throw AccessException if type is not null or not a array
     */
    void assign(std::size_t __n, const Dict& __val) {
        getArray().assign(__n, __val);
    }

    /**
     * @brief Assigns a range to a %vector.
     * This function fills a %vector with copies of the elements in the
     * range (__first,__last).
     *
     * Note that the assignment completely changes the %vector and
     * that the resulting %vector's size is the same as the number
     * of elements assigned.
     *
     * @param __first An input iterator.
     * @param __last An input iterator.
     * @throw AccessException if type is not null or not a array
     */
    template<typename _InputIterator>
    void array_assign(_InputIterator __first, _InputIterator __last) {
        getArray().assign(__first, __last);
    }

    /**
     * @brief Provides access to the data contained in the %vector.
     * This function provides for safer data access.
     * The parameter is first checked that it is in the range of the vector.
     * The function throws out_of_range if the check fails.
     *
     * @tparam T
     * @param index The index of the element for which data should be accessed.
     * @return Dict& Reference to this dictionnary.
     * @throw AccessException if type is not null or not a array
     */
    template<typename T>
    Dict& at(const T& index) {
        return getArray().at(index);
    }

    /**
     * @brief Provides access to the data contained in the %vector.
     * This function provides for safer data access.
     * The parameter is first checked that it is in the range of the vector.
     * The function throws out_of_range if the check fails.
     *
     * @tparam T
     * @param index The index of the element for which data should be accessed.
     * @return const Dict& Reference to this dictionnary.
     * @throw AccessException if type is not null or not a array
     */
    template<typename T>
    const Dict& at(const T& index) const {
        return getArray().at(index);
    }

    /**
     * @brief Returns a read/write reference to the data at the last element of the %vector.
     *
     * @return Dict& Reference to this dictionnary.
     * @throw AccessException if type is not null or not a array
     */
    Dict& back() {
        return getArray().back();
    }

    /**
     * @brief Returns a read-only (constant) reference to the data at the last element of the %vector.
     *
     * @return Dict& Reference to this dictionnary.
     * @throw AccessException if type is not a array
     */
    const Dict& back() const {
        return getArray().back();
    }

    /**
     * @brief Returns a read/write iterator that points to the first element in the %vector.
     * Iteration is done in ordinary element order.
     *
     * @return array_t::iterator
     * @throw AccessException if type is not null or not a array
     */
    array_t::iterator array_begin() {
        return getArray().begin();
    }

    /**
     * @brief Returns a read-only (constant) iterator that points to the first element in the %vector.
     * Iteration is done in ordinary element order.
     *
     * @return array_t::const_iterator
     * @throw AccessException if type is not a array
     */
    array_t::const_iterator array_begin() const {
        return getArray().begin();
    }

    /**
     * @brief Return a read/write iterator that points one past the last element in the %vector.
     * Iteration is done in ordinary element order.
     *
     * @return array_t::iterator
     */
    array_t::iterator array_end() {
        return getArray().end();
    }

    /**
     * @brief Return a read-only (constant) iterator that points one past the last element in the %vector.
     * Iteration is done in ordinary element order.
     *
     * @return array_t::const_iterator
     */
    array_t::const_iterator array_end() const {
        return getArray().end();
    }

    /**
     * @brief Remove element at given position.
     * This function will erase the element at the given position and thus shorten the %vector by one.
     * Note This operation could be expensive and if it is frequently used the user should.
     *
     * @param __position Iterator pointing to element to be erased.
     * @return array_t::iterator An iterator pointing to the next element (or end()).
     */
    array_t::iterator erase(array_t::iterator __position) {
        return getArray().erase(__position);
    }

    /**
     * @brief Remove a range of elements.
     * This function will erase the elements in the range (__first,__last) and shorten the %vector accordingly.
     * Note This operation could be expensive and if it is frequently used the user should consider using std::list.
     * The user is also cautioned that this function only erases the elements,
     * and that if the elements themselves are pointers,
     * the pointed-to memory is not touched in any way.
     * Managing the pointer is the user's responsibility.
     *
     * @param __first Iterator pointing to the first element to be erased.
     * @param __last Iterator pointing to one past the last element to be erased.
     * @return array_t::iterator An iterator pointing to the element pointed to by __last prior to erasing (or end()).
     */
    array_t::iterator erase(array_t::iterator __first, array_t::iterator __last) {
        return getArray().erase(__first, __last);
    }

    /**
     * @brief Returns a read/write reference to the data at the first element of the %vector.
     */
    Dict& front() {
        return getArray().front();
    }

    /**
     * @brief Returns a read-only (constant) reference to the data at the first element of the %vector.
     */
    const Dict& front() const {
        return getArray().front();
    }

    /**
     * @brief Return copy of allocator used to construct this vector.
     */
    array_t::allocator_type array_get_allocator() const {
        return getArray().get_allocator();
    }

    /**
     * @brief Inserts given value into %vector before specified iterator.
     * This function will insert a copy of the given value before the specified location.
     * Note that this kind of operation could be expensive for a %vector and
     * if it is frequently used the user should consider using std::list.
     *
     * @param __position A const_iterator into the %vector.
     * @param __x Data to be inserted.
     * @return array_t::iterator An iterator that points to the inserted data.
     */
    array_t::iterator insert(array_t::iterator __position, const Dict& __x) {
        return getArray().insert(__position, __x);
    }

    /**
     * @brief Inserts a number of copies of given data into the %vector.
     * This function will insert a specified number of copies of the given data before the location specified by
     * position. Note that this kind of operation could be expensive for a %vector and if it is frequently used the user
     * should consider using std::list.
     *
     * @param __position An iterator into the %vector.
     * @param __n Number of elements to be inserted.
     * @param __x Data to be inserted.
     */
    void insert(array_t::iterator __position, std::size_t __n, const Dict& __x) {
        getArray().insert(__position, __n, __x);
    }

    /**
     * @brief Inserts a range into the %vector.
     * This function will insert copies of the data in the range
     * (__first,__last) into the %vector before the location specified
     * by @a pos.
     * Note that this kind of operation could be expensive for a %vector and
     * if it is frequently used the user should consider using std::list.
     *
     * @param __position An iterator into the %vector.
     * @param __first An input iterator.
     * @param __last An input iterator.
     */
    template<typename _InputIterator>
    void insert(array_t::iterator __position, _InputIterator __first, _InputIterator __last) {
        getArray().insert(__position, __first, __last);
    }

    /**
     * @brief Removes last element.
     * This is a typical stack operation.
     * It shrinks the %vector by one.
     *
     * Note that no data is returned, and if the last element's data is needed,
     * it should be retrieved before pop_back() is called.
     */
    void pop_back() {
        getArray().pop_back();
    }

    /**
     * @brief Add data to the end of the %vector.
     * This is a typical stack operation.
     * The function creates an element at the end of the %vector and assigns the given data to it.
     * Due to the nature of a %vector this operation can be done in constant time
     * if the %vector has preallocated space available.
     *
     * @tparam T
     * @param value Data to be added.
     */
    template<typename T>
    void push_back(const T& value) {
        getArray().push_back(value);
    }

    /**
     * @brief Returns a read/write reverse iterator that points to the last element in the %vector.
     * Iteration is done in reverse element order.
     */
    array_t::reverse_iterator array_rbegin() {
        return getArray().rbegin();
    }

    /**
     * @brief Returns a read-only (constant) reverse iterator that points to the last element in the %vector.
     * Iteration is done in reverse element order.
     */
    array_t::const_reverse_iterator array_rbegin() const {
        return getArray().rbegin();
    }

    /**
     * @brief Returns a read/write reverse iterator that points to one before the first element in the %vector.
     * Iteration is done in reverse element order.
     */
    array_t::reverse_iterator array_rend() {
        return getArray().rend();
    }

    /**
     * @brief Returns a read-only (constant) reverse iterator that points
     * to one before the first element in the %vector.
     * Iteration is done in reverse element order.
     */
    array_t::const_reverse_iterator array_rend() const {
        return getArray().rend();
    }

    /**
     * @brief Resizes the %vector to the specified number of elements.
     * This function will %resize the %vector to the specified number of elements.
     * If the number is smaller than the %vector's current size the %vector is truncated,
     * otherwise the %vector is extended and new elements are populated with given data.
     *
     * @param __new_size Number of elements the %vector should contain.
     * @param __x Data with which new elements should be populated.
     */
    void resize(std::size_t __new_size, Dict __x) {
        getArray().resize(__new_size, __x);
    }

    // -------------------------------------------------------------------------
    //  ................................................
    //  ..%%%%...%%%%%...%%%%%%..%%%%%%...%%%%...%%%%%%.
    //  .%%..%%..%%..%%......%%..%%......%%..%%....%%...
    //  .%%..%%..%%%%%.......%%..%%%%....%%........%%...
    //  .%%..%%..%%..%%..%%..%%..%%......%%..%%....%%...
    //  ..%%%%...%%%%%....%%%%...%%%%%%...%%%%.....%%...
    //  ................................................
    // -------------------------------------------------------------------------

    /**
     * @brief check if type of jsonator is a object
     *
     * @return true if type is a object else false
     */
    bool isObject() const {
        return _type == OBJECT_TYPE;
    }

    /**
     * @brief get the object of dict object
     *
     * @return object_t&
     * @throw AccessException if dict type is not a object
     */
    object_t& getObject() {
        if (!isNull() && !isObject()) {
            throw AccessException(*this, "is not a object");
        }
        if (isNull()) {
            _type = OBJECT_TYPE;
            _value.newObject();
        }
        return _value.getObject();
    }

    /**
     * @brief get the object of dict object
     *
     * @return const object_t&
     * @throw AccessException if dict type is not a object
     */
    const object_t& getObject() const {
        if (!isObject()) {
            throw AccessException(*this, "is not a object");
        }
        return _value.getObject();
    }

    /**
     * @brief set value from map
     *
     * @tparam T key
     * @tparam U value
     * @param value
     * @throw AccessException if type is not null or not a object
     */
    template<typename T>
    Dict& operator=(const std::map<std::string, T>& value) {
        newObject();
        typename std::map<std::string, T>::const_iterator it;
        for (it = value.begin(); it != value.end(); ++it) {
            _value.getObject().insert(std::pair<std::string, Dict>(it->first, it->second));
        }
        return *this;
    }

    /**
     * @brief create object
     * @throw AccessException if type is not a null and not a object
     */
    void newObject() {
        if (!isNull() && !isObject()) {
            throw AccessException(*this, "is not a object");
        }
        if (isNull()) {
            _type = OBJECT_TYPE;
            _value.newObject();
        }
    }

    /**
     * @brief get dict from @p key
     *
     * @param key
     * @return Dict& data associated with the key or if the key does not exist,
     * a dict object with that key is created using default values, which is then returned
     * @throw AccessException if type is not a null and not a object
     */
    Dict& operator[](const std::string& key) {
        newObject();
        object_t::iterator it = _value.getObject().find(key);
        if (it != _value.getObject().end()) {
            return it->second;
        }
        return _value.getObject().insert(std::pair<std::string, Dict>(key, Dict())).first->second;
    }

    /**
     * @brief get const dict from @p key
     *
     * @param key
     * @return const Dict&
     * @throw AccessException if type is not a object
     * @throw ChildException if key is not exists
     */
    const Dict& operator[](const std::string& key) const {
        if (!isObject()) {
            throw AccessException(*this, "is not a object");
        }
        object_t::const_iterator it = _value.getObject().find(key);
        if (it != _value.getObject().end()) {
            return it->second;
        }
        throw ChildException(*this, key);
    }

    /**
     * @brief get dict from @p key
     *
     * @param key
     * @return Dict& data associated with the key or if the key does not exist,
     * a dict object with that key is created using default values, which is then returned
     * @throw AccessException if type is not a null and not a object
     */
    Dict& operator[](const char* key) {
        return operator[](std::string(key));
    }

    /**
     * @brief get const dict from @p key
     *
     * @param key
     * @return const Dict&
     * @throw AccessException if type is not a object
     * @throw ChildException if key is not exists
     */
    const Dict& operator[](const char* key) const {
        return operator[](std::string(key));
    }

    /**
     * @brief get dict from @p key
     *
     * @param key
     * @return Dict& data associated with the key or if the key does not exist,
     * a dict object with that key is created using default values, which is then returned
     * @throw AccessException if type is not a null and not a object
     */
    template<std::size_t Size>
    Dict& operator[](const char (&key)[Size]) {
        return operator[](std::string(key));
    }

    /**
     * @brief get const dict from @p key
     *
     * @param key
     * @return const Dict&
     * @throw AccessException if type is not a object
     * @throw ChildException if key is not exists
     */
    template<std::size_t Size>
    const Dict& operator[](const char (&key)[Size]) const {
        return operator[](std::string(key));
    }

    /**
     * @brief check if object contains a @p key
     *
     * @param key
     * @return true if object has key else false
     * @throw AccessException if type is not a object
     */
    bool contains(const std::string& key) const {
        if (!isObject()) {
            throw AccessException(*this, "is not a object");
        }
        return _value.getObject().find(key) != _value.getObject().end();
    }

    /**
     * @brief check if object contains a @p key
     *
     * @param key
     * @return true if object has key else false
     * @throw AccessException if type is not a object
     */
    bool contains(const char* key) const {
        return contains(std::string(key));
    }

    /**
     * @brief check if object contains a @p key
     *
     * @param key
     * @return true if object has key else false
     * @throw AccessException if type is not a object
     */
    template<std::size_t Size>
    bool contains(const char (&key)[Size]) const {
        return contains(std::string(key));
    }

    /**
     * @brief Access to %map data.
     *
     * @param key The key for which data should be retrieved.
     * @return Dict& A reference to the data whose key is equivalent to @a key,
     * if such a data is present in the %map.
     * @throw AccessException if type is not null or not a object
     */
    Dict& at(const std::string& key) {
        return getObject().at(key);
    }

    /**
     * @brief Access to %map data.
     *
     * @param key The key for which data should be retrieved.
     * @return const Dict& A reference to the data whose key is equivalent to @a key,
     * if such a data is present in the %map.
     * @throw AccessException if type is not a object
     */
    const Dict& at(const std::string& key) const {
        return getObject().at(key);
    }

    /**
     * @brief Access to %map data.
     *
     * @param key The key for which data should be retrieved.
     * @return Dict& A reference to the data whose key is equivalent to @a key,
     * if such a data is present in the %map.
     * @throw AccessException if type is not null or not a object
     */
    Dict& at(const char* key) {
        return getObject().at(key);
    }

    /**
     * @brief Access to %map data.
     *
     * @param key The key for which data should be retrieved.
     * @return const Dict& A reference to the data whose key is equivalent to @a key,
     * if such a data is present in the %map.
     * @throw AccessException if type is not a object
     */
    const Dict& at(const char* key) const {
        return getObject().at(key);
    }

    /**
     * @brief Access to %map data.
     *
     * @param key The key for which data should be retrieved.
     * @return Dict& A reference to the data whose key is equivalent to @a key,
     * if such a data is present in the %map.
     * @throw AccessException if type is not null or not a object
     */
    template<std::size_t Size>
    Dict& at(const char* (&key)[Size]) {
        return getObject().at(key);
    }

    /**
     * @brief Access to %map data.
     *
     * @param key The key for which data should be retrieved.
     * @return const Dict& A reference to the data whose key is equivalent to @a key,
     * if such a data is present in the %map.
     * @throw AccessException if type is not a object
     */
    template<std::size_t Size>
    const Dict& at(const char* (&key)[Size]) const {
        return getObject().at(key);
    }

    /**
     * @brief Returns a read/write iterator that points to the first pair in the %map.
     * Iteration is done in ascending order according to the keys.
     *
     * @return object_t::iterator
     * @throw AccessException if type is not null or not a object
     */
    object_t::iterator object_begin() {
        return getObject().begin();
    }

    /**
     * @brief Returns a read-only (constant) iterator that points to the first pair in the %map.
     * Iteration is done in ascending order according to the keys.
     *
     * @return object_t::const_iterator
     * @throw AccessException if type is not a object
     */
    object_t::const_iterator object_begin() const {
        return getObject().begin();
    }

    /**
     * @brief Finds the number of elements with given key.
     * This function only makes sense for multimaps;
     * for map the result will either be 0 (not present) or 1 (present).
     *
     * @param __x Key of (key, value) pairs to be located.
     * @return std::size_t Number of elements with specified key.
     */
    std::size_t count(const std::string& __x) const {
        return getObject().count(__x);
    }

    /**
     * @brief Return a read/write iterator that points one past the last pair in the %map.
     * Iteration is done in ascending order according to the keys.
     *
     * @return object_t::iterator
     */
    object_t::iterator object_end() {
        return getObject().end();
    }

    /**
     * @brief Returns a read-only (constant) iterator that points one past the last pair in the %map.
     * Iteration is done in ascending order according to the keys.
     *
     * @return object_t::const_iterator
     */
    object_t::const_iterator object_end() const {
        return getObject().end();
    }

    /**
     * @brief Finds a subsequence matching given key.
     * This function is equivalent to std::make_pair(c.lower_bound(val), c.upper_bound(val))
     * (but is faster than making the calls separately).
     * This function probably only makes sense for multimaps.
     *
     * @param __x Key of (key, value) pairs to be located.
     * @return std::pair<object_t::iterator, object_t::iterator>
     * Pair of iterators that possibly points to the subsequence matching given key.
     */
    std::pair<object_t::iterator, object_t::iterator> equal_range(const std::string& __x) {
        return getObject().equal_range(__x);
    }

    /**
     * @brief Finds a subsequence matching given key.
     * This function is equivalent to std::make_pair(c.lower_bound(val), c.upper_bound(val))
     * (but is faster than making the calls separately).
     * This function probably only makes sense for multimaps.
     *
     * @param __x Key of (key, value) pairs to be located.
     * @return std::pair<object_t::const_iterator, object_t::const_iterator>
     * Pair of read-only (constant) iterators that possibly points to the subsequence matching given key.
     */
    std::pair<object_t::const_iterator, object_t::const_iterator> equal_range(const std::string& __x) const {
        return getObject().equal_range(__x);
    }

    /**
     * @brief Erases an element from a %map.
     * This function erases an element, pointed to by the given iterator, from a %map.
     * Note that this function only erases the element,
     * and that if the element is itself a pointer,
     * the pointed-to memory is not touched in any way.
     * Managing the pointer is the user's responsibility.
     *
     * @param __position An iterator pointing to the element to be erased.
     */
    void erase(object_t::iterator __position) {
        getObject().erase(__position);
    }

    /**
     * @brief Erases elements according to the provided key.
     * This function erases all the elements located by the given key from a %map.
     * Note that this function only erases the element,
     * and that if the element is itself a pointer,
     * the pointed-to memory is not touched in any way.
     * Managing the pointer is the user's responsibility.
     *
     * @param __x Key of element to be erased.
     * @return std::size_t The number of elements erased.
     */
    std::size_t erase(const std::string& __x) {
        return getObject().erase(__x);
    }

    /**
     * @brief Erases a (__first,__last) range of elements from a %map.
     * This function erases a sequence of elements from a %map.
     * Note that this function only erases the element, and that if
     * the element is itself a pointer, the pointed-to memory is not touched
     * in any way.
     * Managing the pointer is the user's responsibility.
     *
     * @param __first Iterator pointing to the start of the range to be erased.
     * @param __last Iterator pointing to the end of the range to be erased.
     */
    void erase(object_t::iterator __first, object_t::iterator __last) {
        getObject().erase(__first, __last);
    }

    /**
     * @brief Tries to locate an element in a %map.
     * This function takes a key and tries to locate the element with which the key matches.
     * If successful the function returns an iterator pointing to the sought after %pair.
     * If unsuccessful it returns the past-the-end ( @c end() ) iterator.
     *
     * @param __x Key of (key, value) %pair to be located.
     * @return object_t::iterator Iterator pointing to sought-after element, or end() if not found.
     */
    object_t::iterator find(const std::string& __x) {
        return getObject().find(__x);
    }

    /**
     * @brief Tries to locate an element in a %map.
     * This function takes a key and tries to locate the element with which the key matches.
     * If successful the function returns a constant iterator pointing to the sought after %pair.
     * If unsuccessful it returns the past-the-end ( @c end() ) iterator.
     *
     * @param __x Key of (key, value) %pair to be located.
     * @return object_t::const_iterator Read-only (constant) iterator pointing to sought-after element, or end() if not
     * found.
     */
    object_t::const_iterator find(const std::string& __x) const {
        return getObject().find(__x);
    }

    /**
     * @brief Return copy of allocator used to construct this object.
     */
    object_t::allocator_type object_get_allocator() const {
        return getObject().get_allocator();
    }

    /**
     * @brief Attempts to insert a std::pair into the %map.
     * This function attempts to insert a (key, value) %pair into the %map.
     * A %map relies on unique keys and
     * thus a %pair is only inserted if its first element (the key) is not already present in the %map.
     * Insertion requires logarithmic time.
     *
     * @param __x Pair to be inserted (see std::make_pair for easy creation of pairs).
     * @return std::pair<object_t::iterator, bool> A pair,
     * of which the first element is an iterator that points to the possibly inserted pair,
     * and the second is a bool that is true if the pair was actually inserted.
     */
    std::pair<object_t::iterator, bool> insert(const object_t::value_type& __x) {
        return getObject().insert(__x);
    }

    /**
     * @brief Attempts to insert a std::pair into the %map.
     * This function is not concerned about whether the insertion
     * took place, and thus does not return a boolean like the
     * single-argument insert() does.  Note that the first
     * parameter is only a hint and can potentially improve the
     * performance of the insertion process.
     * A bad hint would cause no gains in efficiency.
     *
     * See
     * https://gcc.gnu.org/onlinedocs/libstdc++/manual/associative.html#containers.associative.insert_hints
     * for more on @a hinting.
     *
     * Insertion requires logarithmic time (if the hint is not taken).
     *
     * @param __position An iterator that serves as a hint as to where the pair should be inserted.
     * @param __x Pair to be inserted (see std::make_pair for easy creation of pairs).
     * @return object_t::iterator An iterator that points to the element with
     * key of @a __x (may or may not be the %pair passed in).
     */
    object_t::iterator insert(object_t::iterator __position, const object_t::value_type& __x) {
        return getObject().insert(__position, __x);
    }

    /**
     * @brief Template function that attempts to insert a range of elements.
     * Complexity similar to that of the range constructor.
     *
     * @param __first Iterator pointing to the start of the range to be inserted.
     * @param __last Iterator pointing to the end of the range.
     *
     */
    template<typename _InputIterator>
    void insert(_InputIterator __first, _InputIterator __last) {
        return getObject().insert(__first, __last);
    }

    /**
     * @return object_t::key_compare key comparison object out of which the %map was constructed.
     */
    object_t::key_compare key_comp() const {
        return getObject().key_comp();
    }

    /**
     * @brief Finds the beginning of a subsequence matching given key.
     * This function returns the first element of a subsequence of elements that matches the given key.
     * If unsuccessful it returns an iterator pointing to
     * the first element that has a greater value than given key or end() if no such element exists.
     *
     * @param __x Key of (key, value) pair to be located.
     * @return object_t::iterator Iterator pointing to first element equal to or greater than key, or end().
     */
    object_t::iterator lower_bound(const std::string& __x) {
        return getObject().lower_bound(__x);
    }

    /**
     * @brief Finds the beginning of a subsequence matching given key.
     * This function returns the first element of a subsequence of elements that matches the given key.
     * If unsuccessful it returns an iterator pointing to
     * the first element that has a greater value than given key or end() if no such element exists.
     *
     * @param __x Key of (key, value) pair to be located.
     * @return object_t::const_iterator Read-only (constant) iterator pointing to
     * first element equal to or greater than key, or end().
     */
    object_t::const_iterator lower_bound(const std::string& __x) const {
        return getObject().lower_bound(__x);
    }

    /**
     * @brief Returns a read/write reverse iterator that points to the last pair in the %map.
     * Iteration is done in descending order according to the keys.
     */
    object_t::reverse_iterator object_rbegin() {
        return getObject().rbegin();
    }

    /**
     * @brief Returns a read-only (constant) reverse iterator that points to the last pair in the %map.
     * Iteration is done in descending order according to the keys.
     */
    object_t::const_reverse_iterator object_rbegin() const {
        return getObject().rbegin();
    }

    /**
     * @brief Returns a read/write reverse iterator that points to one before the first pair in the %map.
     * Iteration is done in descending order according to the keys.
     */
    object_t::reverse_iterator object_rend() {
        return getObject().rend();
    }

    /**
     * @brief Returns a read-only (constant) reverse iterator that points
     * to one before the first pair in the %map.
     * Iteration is done in descending order according to the keys.
     */
    object_t::const_reverse_iterator object_rend() const {
        return getObject().rend();
    }

    /**
     * @brief Finds the end of a subsequence matching given key.
     *
     * @param __x Key of (key, value) pair to be located.
     * @return object_t::iterator Iterator pointing to the first element greater than key, or end().
     */
    object_t::iterator upper_bound(const std::string& __x) {
        return getObject().upper_bound(__x);
    }

    /**
     * @brief Finds the end of a subsequence matching given key.
     *
     * @param __x Key of (key, value) pair to be located.
     * @return object_t::const_iterator Read-only (constant) iterator pointing to first iterator greater than key, or
     * end().
     */
    object_t::const_iterator upper_bound(const std::string& __x) const {
        return getObject().upper_bound(__x);
    }

    /**
     * @brief Returns a value comparison object, built from the key comparison object out of
     * which the %map was constructed.
     */
    object_t::value_compare value_comp() const {
        return getObject().value_comp();
    }

    // -------------------------------------------------------------------------
    //  ..................................................
    //  ..%%%%....%%%%...%%...%%..%%...%%...%%%%...%%..%%.
    //  .%%..%%..%%..%%..%%%.%%%..%%%.%%%..%%..%%..%%%.%%.
    //  .%%......%%..%%..%%.%.%%..%%.%.%%..%%..%%..%%.%%%.
    //  .%%..%%..%%..%%..%%...%%..%%...%%..%%..%%..%%..%%.
    //  ..%%%%....%%%%...%%...%%..%%...%%...%%%%...%%..%%.
    //  ..................................................
    // -------------------------------------------------------------------------

    /**
     * @brief Returns the total number of elements that the %string or %vector can hold before needing to allocate more
     * memory.
     *
     * @return std::size_t
     */
    std::size_t capacity() const {
        std::size_t ret;
        switch (_type) {
            case NULL_TYPE:
            case BOOLEAN_TYPE:
            case NUMBER_TYPE:
            case OBJECT_TYPE:
                throw MethodException(*this, "capacity");
                break;
            case STRING_TYPE:
                ret = getString().capacity();
                break;
            case ARRAY_TYPE:
                ret = getArray().capacity();
                break;
        }
        return ret;
    }

    /**
     * @brief Return true if the %string or %vector or %map is empty.
     */
    bool empty() const {
        bool ret;
        switch (_type) {
            case NULL_TYPE:
            case BOOLEAN_TYPE:
            case NUMBER_TYPE:
                throw MethodException(*this, "empty");
                break;
            case STRING_TYPE:
                ret = getString().empty();
                break;
            case ARRAY_TYPE:
                ret = getArray().empty();
                break;
            case OBJECT_TYPE:
                ret = getObject().empty();
                break;
        }
        return ret;
    }

    /**
     * @return std::size_t size() of the largest possible %string or %vector or %map.
     */
    std::size_t max_size() const {
        std::size_t ret;
        switch (_type) {
            case NULL_TYPE:
            case BOOLEAN_TYPE:
            case NUMBER_TYPE:
                throw MethodException(*this, "max_size");
                break;
            case STRING_TYPE:
                ret = getString().max_size();
                break;
            case ARRAY_TYPE:
                ret = getArray().max_size();
                break;
            case OBJECT_TYPE:
                ret = getObject().max_size();
                break;
        }
        return ret;
    }

    /**
     * @brief Attempt to preallocate enough memory for specified number of elements.
     * This function attempts to reserve enough memory for the %string or %vector to
     * hold the specified number of elements.
     * If the number requested is more than max_size(), length_error is thrown.
     * The advantage of this function is that if optimal code is a necessity and
     * the user can determine the number of elements that will be required,
     * the user can reserve the memory in %advance,
     * and thus prevent a possible reallocation of memory and copying of %vector data.
     *
     * @param __res_arg Number of elements required.
     * @throw std::length_error If res_arg exceeds max_size().
     */
    void reserve(std::size_t __res_arg = 0) {
        switch (_type) {
            case NULL_TYPE:
            case BOOLEAN_TYPE:
            case NUMBER_TYPE:
            case OBJECT_TYPE:
                throw MethodException(*this, "reserve");
                break;
            case STRING_TYPE:
                getString().reserve(__res_arg);
                break;
            case ARRAY_TYPE:
                getArray().reserve(__res_arg);
                break;
        }
    }

    /**
     * @brief Resizes the %string or %vector to the specified number of element.
     * This function will %resize the %string or %vector to the specified number of elements.
     * If the number is smaller than the %string or %vector's current size the %string or %vector is truncated,
     * otherwise the %string or %vector is extended and new elements are populated with given data.
     *
     * @param __n Number of elements the %string or %vector should contain.
     */
    void resize(std::size_t __n) {
        switch (_type) {
            case NULL_TYPE:
            case BOOLEAN_TYPE:
            case NUMBER_TYPE:
            case OBJECT_TYPE:
                throw MethodException(*this, "resize");
                break;
            case STRING_TYPE:
                getString().resize(__n);
                break;
            case ARRAY_TYPE:
                getArray().resize(__n);
                break;
        }
    }

    /**
     * @brief Returns the number of elements in the %string or %vector or %map.
     */
    std::size_t size() const {
        std::size_t ret;
        switch (_type) {
            case NULL_TYPE:
            case BOOLEAN_TYPE:
            case NUMBER_TYPE:
                throw MethodException(*this, "size");
                break;
            case STRING_TYPE:
                ret = getString().size();
                break;
            case ARRAY_TYPE:
                ret = getArray().size();
                break;
            case OBJECT_TYPE:
                ret = getObject().size();
                break;
        }
        return ret;
    }

    /**
     * @brief Dict equality comparison.
     *
     * @param value a dict
     * @return true if the value and the dict are equal.
     */
    bool operator==(const Dict& value) const {
        bool ret;
        if (_type == value._type) {
            switch (_type) {
                case NULL_TYPE:
                    ret = true;
                    break;
                case BOOLEAN_TYPE:
                    ret = _value.getBoolean() == value._value.getBoolean();
                    break;
                case NUMBER_TYPE:
                    ret = _value.getNumber() == value._value.getNumber();
                    break;
                case STRING_TYPE:
                    ret = _value.getString() == value._value.getString();
                    break;
                case ARRAY_TYPE:
                    ret = _value.getArray() == value._value.getArray();
                    break;
                case OBJECT_TYPE:
                    ret = _value.getObject() == value._value.getObject();
                    break;
            }
        }
        else {
            ret = false;
        }
        return ret;
    }

    /**
     * @brief Dict not equality comparison.
     *
     * @param value a dict
     * @return true if the value and the dict are not equal.
     */
    bool operator!=(const Dict& value) const {
        return !(operator==(value));
    }

    /**
     * @brief Dict ordering relation.
     *
     * @param value A dict.
     * @return True if dict is lexicographically greater than value.
     */
    bool operator>(const Dict& value) const {
        bool ret;
        if (_type == value._type) {
            switch (_type) {
                case NULL_TYPE:
                    ret = true;
                    break;
                case BOOLEAN_TYPE:
                    ret = _value.getBoolean() > value._value.getBoolean();
                    break;
                case NUMBER_TYPE:
                    ret = _value.getNumber() > value._value.getNumber();
                    break;
                case STRING_TYPE:
                    ret = _value.getString() > value._value.getString();
                    break;
                case ARRAY_TYPE:
                    ret = _value.getArray() > value._value.getArray();
                    break;
                case OBJECT_TYPE:
                    ret = _value.getObject() > value._value.getObject();
                    break;
            }
        }
        else {
            ret = false;
        }
        return ret;
    }

    /**
     * @brief Dict ordering relation.
     *
     * @param value A dict.
     * @return True if dict is lexicographically less than value.
     */
    bool operator<(const Dict& value) const {
        bool ret;
        if (_type == value._type) {
            switch (_type) {
                case NULL_TYPE:
                    ret = true;
                    break;
                case BOOLEAN_TYPE:
                    ret = _value.getBoolean() < value._value.getBoolean();
                    break;
                case NUMBER_TYPE:
                    ret = _value.getNumber() < value._value.getNumber();
                    break;
                case STRING_TYPE:
                    ret = _value.getString() < value._value.getString();
                    break;
                case ARRAY_TYPE:
                    ret = _value.getArray() < value._value.getArray();
                    break;
                case OBJECT_TYPE:
                    ret = _value.getObject() < value._value.getObject();
                    break;
            }
        }
        else {
            ret = false;
        }
        return ret;
    }

    /**
     * @brief Dict ordering relation.
     *
     * @param value A dict.
     * @return True if dict is lexicographically greater or equal than value.
     */
    bool operator>=(const Dict& value) const {
        bool ret;
        if (_type == value._type) {
            switch (_type) {
                case NULL_TYPE:
                    ret = true;
                    break;
                case BOOLEAN_TYPE:
                    ret = _value.getBoolean() >= value._value.getBoolean();
                    break;
                case NUMBER_TYPE:
                    ret = _value.getNumber() >= value._value.getNumber();
                    break;
                case STRING_TYPE:
                    ret = _value.getString() >= value._value.getString();
                    break;
                case ARRAY_TYPE:
                    ret = _value.getArray() >= value._value.getArray();
                    break;
                case OBJECT_TYPE:
                    ret = _value.getObject() >= value._value.getObject();
                    break;
            }
        }
        else {
            ret = false;
        }
        return ret;
    }

    /**
     * @brief Dict ordering relation.
     *
     * @param value A dict.
     * @return True if dict is lexicographically less or equal than value.
     */
    bool operator<=(const Dict& value) const {
        bool ret;
        if (_type == value._type) {
            switch (_type) {
                case NULL_TYPE:
                    ret = true;
                    break;
                case BOOLEAN_TYPE:
                    ret = _value.getBoolean() <= value._value.getBoolean();
                    break;
                case NUMBER_TYPE:
                    ret = _value.getNumber() <= value._value.getNumber();
                    break;
                case STRING_TYPE:
                    ret = _value.getString() <= value._value.getString();
                    break;
                case ARRAY_TYPE:
                    ret = _value.getArray() <= value._value.getArray();
                    break;
                case OBJECT_TYPE:
                    ret = _value.getObject() <= value._value.getObject();
                    break;
            }
        }
        else {
            ret = false;
        }
        return ret;
    }

    /**
     * @brief Use operator + if exist.
     *
     * @return Dict A new Dict.
     */
    Dict operator+() const {
        Dict ret;
        switch (_type) {
            case NULL_TYPE:
            case STRING_TYPE:
            case ARRAY_TYPE:
            case OBJECT_TYPE:
                throw MethodException(*this, "operator+");
                break;
            case BOOLEAN_TYPE:
                ret = +_value.getBoolean();
                break;
            case NUMBER_TYPE:
                ret = +_value.getNumber();
                break;
        }
        return ret;
    }

    /**
     * @brief Use operator - if exist.
     *
     * @return Dict A new Dict.
     */
    Dict operator-() const {
        Dict ret;
        switch (_type) {
            case NULL_TYPE:
            case STRING_TYPE:
            case ARRAY_TYPE:
            case OBJECT_TYPE:
                throw MethodException(*this, "operator+");
                break;
            case BOOLEAN_TYPE:
                ret = -_value.getBoolean();
                break;
            case NUMBER_TYPE:
                ret = -_value.getNumber();
                break;
        }
        return ret;
    }

    /**
     * @brief Concatenate two strings.
     *
     * @param value A string.
     * @return Dict A new Dict.
     */
    Dict operator+(const std::string& value) const {
        Dict ret;
        switch (_type) {
            case NULL_TYPE:
            case ARRAY_TYPE:
            case OBJECT_TYPE:
            case BOOLEAN_TYPE:
            case NUMBER_TYPE:
                throw MethodException(*this, "operator+");
                break;
            case STRING_TYPE:
                ret = _value.getString() + value;
        }
        return ret;
    }

    /**
     * @brief Concatenate two strings.
     *
     * @param value A C string.
     * @return Dict A new Dict.
     */
    Dict operator+(const char* value) const {
        Dict ret;
        switch (_type) {
            case NULL_TYPE:
            case ARRAY_TYPE:
            case OBJECT_TYPE:
            case BOOLEAN_TYPE:
            case NUMBER_TYPE:
                throw MethodException(*this, "operator+");
                break;
            case STRING_TYPE:
                ret = _value.getString() + value;
        }
        return ret;
    }

    /**
     * @brief Concatenate two strings.
     *
     * @tparam Size Length of value.
     * @return Dict A new Dict.
     */
    template<std::size_t Size>
    Dict operator+(const char (&value)[Size]) const {
        Dict ret;
        switch (_type) {
            case NULL_TYPE:
            case ARRAY_TYPE:
            case OBJECT_TYPE:
            case BOOLEAN_TYPE:
            case NUMBER_TYPE:
                throw MethodException(*this, "operator+");
                break;
            case STRING_TYPE:
                ret = _value.getString() + value;
        }
        return ret;
    }

    /**
     * @brief Use operator + if exist.
     *
     * @tparam T Type of value.
     * @param value A value.
     * @return Dict A new Dict.
     */
    template<typename T>
    Dict operator+(const T& value) const {
        Dict ret;
        switch (_type) {
            case NULL_TYPE:
            case ARRAY_TYPE:
            case OBJECT_TYPE:
            case STRING_TYPE:
                throw MethodException(*this, "operator+");
                break;
            case BOOLEAN_TYPE:
                ret = _value.getBoolean() + value;
                break;
            case NUMBER_TYPE:
                ret = _value.getNumber() + value;
                break;
        }
        return ret;
    }

    /**
     * @brief Use operator - if exist.
     *
     * @tparam T Type of value.
     * @param value A value.
     * @return Dict A new Dict.
     */
    template<typename T>
    Dict operator-(const T& value) const {
        Dict ret;
        switch (_type) {
            case NULL_TYPE:
            case ARRAY_TYPE:
            case OBJECT_TYPE:
            case STRING_TYPE:
                throw MethodException(*this, "operator-");
                break;
            case BOOLEAN_TYPE:
                ret = _value.getBoolean() - value;
                break;
            case NUMBER_TYPE:
                ret = _value.getNumber() - value;
                break;
        }
        return ret;
    }

    /**
     * @brief Use operator * if exist.
     *
     * @tparam T Type of value.
     * @param value A value.
     * @return Dict A new Dict.
     */
    template<typename T>
    Dict operator*(const T& value) const {
        Dict ret;
        switch (_type) {
            case NULL_TYPE:
            case ARRAY_TYPE:
            case OBJECT_TYPE:
            case STRING_TYPE:
                throw MethodException(*this, "operator*");
                break;
            case BOOLEAN_TYPE:
                ret = _value.getBoolean() * value;
                break;
            case NUMBER_TYPE:
                ret = _value.getNumber() * value;
                break;
        }
        return ret;
    }

    /**
     * @brief Use operator / if exist.
     *
     * @tparam T Type of value.
     * @param value A value.
     * @return Dict A new Dict.
     */
    template<typename T>
    Dict operator/(const T& value) const {
        Dict ret;
        switch (_type) {
            case NULL_TYPE:
            case ARRAY_TYPE:
            case OBJECT_TYPE:
            case STRING_TYPE:
                throw MethodException(*this, "operator/");
                break;
            case BOOLEAN_TYPE:
                ret = _value.getBoolean() / value;
                break;
            case NUMBER_TYPE:
                ret = _value.getNumber() / value;
                break;
        }
        return ret;
    }

    /**
     * @brief Use operator % if exist.
     *
     * @tparam T Type of value.
     * @param value A value.
     * @return Dict A new Dict.
     */
    template<typename T>
    Dict operator%(const T& value) const {
        Dict ret;
        switch (_type) {
            case NULL_TYPE:
            case ARRAY_TYPE:
            case OBJECT_TYPE:
            case STRING_TYPE:
                throw MethodException(*this, "operator%");
                break;
            case BOOLEAN_TYPE:
                ret = _value.getBoolean() - static_cast<long>(_value.getBoolean() / value) * value;
                break;
            case NUMBER_TYPE:
                ret = _value.getNumber() - static_cast<long>(_value.getNumber() / value) * value;
                break;
        }
        return ret;
    }

    // Dict operator~() const {
    //     Dict ret;
    //     switch (_type) {
    //         case NULL_TYPE:
    //         case ARRAY_TYPE:
    //         case OBJECT_TYPE:
    //         case STRING_TYPE:
    //         case BOOLEAN_TYPE:
    //             throw MethodException(*this, "operator~");
    //             break;
    //         case NUMBER_TYPE:
    //             ret = ~static_cast<long>(_value.getNumber());
    //             break;
    //     }
    //     return ret;
    // }

    /**
     * @brief Use operator & if exist.
     *
     * @tparam T Type of value.
     * @param value A value.
     * @return Dict A new Dict.
     */
    template<typename T>
    Dict operator&(const T& value) const {
        Dict ret;
        switch (_type) {
            case NULL_TYPE:
            case ARRAY_TYPE:
            case OBJECT_TYPE:
            case STRING_TYPE:
                throw MethodException(*this, "operator&");
                break;
            case BOOLEAN_TYPE:
                ret = _value.getBoolean() & value;
                break;
            case NUMBER_TYPE:
                ret = _value.getNumber() & value;
                break;
        }
        return ret;
    }

    /**
     * @brief Use operator | if exist.
     *
     * @tparam T Type of value.
     * @param value A value.
     * @return Dict A new Dict.
     */
    template<typename T>
    Dict operator|(const T& value) const {
        Dict ret;
        switch (_type) {
            case NULL_TYPE:
            case ARRAY_TYPE:
            case OBJECT_TYPE:
            case STRING_TYPE:
                throw MethodException(*this, "operator|");
                break;
            case BOOLEAN_TYPE:
                ret = _value.getBoolean() | value;
                break;
            case NUMBER_TYPE:
                ret = _value.getNumber() | value;
                break;
        }
        return ret;
    }

    /**
     * @brief Use operator ^ if exist.
     *
     * @tparam T Type of value.
     * @param value A value.
     * @return Dict A new Dict.
     */
    template<typename T>
    Dict operator^(const T& value) const {
        Dict ret;
        switch (_type) {
            case NULL_TYPE:
            case ARRAY_TYPE:
            case OBJECT_TYPE:
            case STRING_TYPE:
                throw MethodException(*this, "operator^");
                break;
            case BOOLEAN_TYPE:
                ret = _value.getBoolean() ^ value;
                break;
            case NUMBER_TYPE:
                ret = _value.getNumber() ^ value;
                break;
        }
        return ret;
    }

    /**
     * @brief get the @c T of dict object.
     *
     * @tparam T Return type.
     * @return T Cast of type.
     */
    template<typename T>
    T get() const {
        return *this;
    }

    /**
     * @brief get the @p T of dict object
     *
     * @tparam T
     * @param ret
     */
    template<typename T>
    void get(T& ret) const {
        ret = get<T>();
    }

    /**
     * @brief get dict to deque
     *
     * @tparam T
     */
    template<typename T>
    operator std::deque<T>() const {
        std::deque<T> ret;
        switch (_type) {
            case ARRAY_TYPE: {
                for (std::size_t i = 0; i < _value.getArray().size(); ++i) {
                    ret.push_back(_value.getArray()[i]);
                }
                break;
            }
            case OBJECT_TYPE: {
                for (object_t::const_iterator it = _value.getObject().begin(); it != _value.getObject().end(); ++it) {
                    ret.push_back(it->second);
                }
                break;
            }
            default:
                break;
        }
        return ret;
    }

    /**
     * @brief get dict to list
     *
     * @tparam T
     */
    template<typename T>
    operator std::list<T>() const {
        std::list<T> ret;
        switch (_type) {
            case ARRAY_TYPE:
                for (std::size_t i = 0; i < _value.getArray().size(); ++i) {
                    ret.push_back(_value.getArray()[i]);
                }
                break;
            case OBJECT_TYPE:
                for (object_t::const_iterator it = _value.getObject().begin(); it != _value.getObject().end(); ++it) {
                    ret.push_back(it->second);
                }
                break;
            default:
                break;
        }
        return ret;
    }

    /**
     * @brief get dict to map
     *
     * @tparam T
     * @return std::map<std::string, T>
     */
    template<typename T>
    operator std::map<std::string, T>() const {
        std::map<std::string, T> ret;
        if (isObject()) {
            for (object_t::const_iterator it = _value.getObject().begin(); it != _value.getObject().end(); ++it) {
                ret.insert(std::pair<std::string, T>(it->first, it->second));
            }
        }
        return ret;
    }

    /**
     * @brief get dict to map
     *
     * @tparam T key
     * @tparam U value
     */
    template<typename T, typename U>
    operator std::map<T, U>() const {
        std::map<T, U> ret;
        if (isArray()) {
            for (std::size_t i = 0; i < _value.getArray().size(); ++i) {
                ret.insert(std::pair<T, U>(i, (*_value._array)[i]));
            }
        }
        return ret;
    }

    /**
     * @brief get dict to queue
     *
     * @tparam T
     */
    template<typename T>
    operator std::queue<T>() const {
        std::queue<T> ret;
        switch (_type) {
            case ARRAY_TYPE:
                for (std::size_t i = 0; i < _value.getArray().size(); ++i) {
                    ret.push(_value.getArray()[i]);
                }
                break;
            case OBJECT_TYPE:
                for (object_t::const_iterator it = _value.getObject().begin(); it != _value.getObject().end(); ++it) {
                    ret.push(it->second);
                }
                break;
            default:
                break;
        }
        return ret;
    }

    /**
     * @brief get dict to set
     *
     * @tparam T
     */
    template<typename T>
    operator std::set<T>() const {
        std::set<T> ret;
        switch (_type) {
            case ARRAY_TYPE:
                for (std::size_t i = 0; i < _value.getArray().size(); ++i) {
                    ret.insert(_value.getArray()[i]);
                }
                break;
            case OBJECT_TYPE:
                for (object_t::const_iterator it = _value.getObject().begin(); it != _value.getObject().end(); ++it) {
                    ret.insert(it->second);
                }
                break;
            default:
                break;
        }
        return ret;
    }

    /**
     * @brief get dict to stack
     *
     * @tparam T
     */
    template<typename T>
    operator std::stack<T>() const {
        std::stack<T> ret;
        switch (_type) {
            case ARRAY_TYPE:
                for (std::size_t i = 0; i < _value.getArray().size(); ++i) {
                    ret.insert(_value.getArray()[i]);
                }
                break;
            case OBJECT_TYPE:
                for (object_t::const_iterator it = _value.getObject().begin(); it != _value.getObject().end(); ++it) {
                    ret.insert(it->second);
                }
                break;
            default:
                break;
        }
        return ret;
    }

    /**
     * @brief get dict to vector
     *
     * @tparam T
     */
    template<typename T>
    operator std::vector<T>() const {
        std::vector<T> ret;
        switch (_type) {
            case ARRAY_TYPE:
                ret.reserve(_value.getArray().size());
                for (std::size_t i = 0; i < _value.getArray().size(); ++i) {
                    ret.push_back(_value.getArray()[i]);
                }
                break;
            case OBJECT_TYPE:
                ret.reserve(_value.getObject().size());
                for (object_t::const_iterator it = _value.getObject().begin(); it != _value.getObject().end(); ++it) {
                    ret.push_back(it->second);
                }
                break;
            default:
                break;
        }
        return ret;
    }
};

} // namespace blet

#endif // _BLET_DICT_H_