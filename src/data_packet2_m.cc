//
// Generated file, do not edit! Created by nedtool 5.4 from data_packet2.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "data_packet2_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(Data_packet2)

Data_packet2::Data_packet2(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->isRequest = false;
    this->sequenceNumber = 0;
    this->type = 0;
    this->senderID = 0;
    this->size = 0;
    this->isD2D = false;
}

Data_packet2::Data_packet2(const Data_packet2& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

Data_packet2::~Data_packet2()
{
}

Data_packet2& Data_packet2::operator=(const Data_packet2& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void Data_packet2::copy(const Data_packet2& other)
{
    this->isRequest = other.isRequest;
    this->sequenceNumber = other.sequenceNumber;
    this->type = other.type;
    this->senderID = other.senderID;
    this->size = other.size;
    this->data = other.data;
    this->isD2D = other.isD2D;
}

void Data_packet2::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->isRequest);
    doParsimPacking(b,this->sequenceNumber);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->senderID);
    doParsimPacking(b,this->size);
    doParsimPacking(b,this->data);
    doParsimPacking(b,this->isD2D);
}

void Data_packet2::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->isRequest);
    doParsimUnpacking(b,this->sequenceNumber);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->senderID);
    doParsimUnpacking(b,this->size);
    doParsimUnpacking(b,this->data);
    doParsimUnpacking(b,this->isD2D);
}

bool Data_packet2::getIsRequest() const
{
    return this->isRequest;
}

void Data_packet2::setIsRequest(bool isRequest)
{
    this->isRequest = isRequest;
}

int Data_packet2::getSequenceNumber() const
{
    return this->sequenceNumber;
}

void Data_packet2::setSequenceNumber(int sequenceNumber)
{
    this->sequenceNumber = sequenceNumber;
}

int Data_packet2::getType() const
{
    return this->type;
}

void Data_packet2::setType(int type)
{
    this->type = type;
}

int Data_packet2::getSenderID() const
{
    return this->senderID;
}

void Data_packet2::setSenderID(int senderID)
{
    this->senderID = senderID;
}

int Data_packet2::getSize() const
{
    return this->size;
}

void Data_packet2::setSize(int size)
{
    this->size = size;
}

payload& Data_packet2::getData()
{
    return this->data;
}

void Data_packet2::setData(const payload& data)
{
    this->data = data;
}

bool Data_packet2::getIsD2D() const
{
    return this->isD2D;
}

void Data_packet2::setIsD2D(bool isD2D)
{
    this->isD2D = isD2D;
}

class Data_packet2Descriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    Data_packet2Descriptor();
    virtual ~Data_packet2Descriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(Data_packet2Descriptor)

Data_packet2Descriptor::Data_packet2Descriptor() : omnetpp::cClassDescriptor("Data_packet2", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

Data_packet2Descriptor::~Data_packet2Descriptor()
{
    delete[] propertynames;
}

bool Data_packet2Descriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Data_packet2 *>(obj)!=nullptr;
}

const char **Data_packet2Descriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *Data_packet2Descriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int Data_packet2Descriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount() : 7;
}

unsigned int Data_packet2Descriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *Data_packet2Descriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "isRequest",
        "sequenceNumber",
        "type",
        "senderID",
        "size",
        "data",
        "isD2D",
    };
    return (field>=0 && field<7) ? fieldNames[field] : nullptr;
}

int Data_packet2Descriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "isRequest")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "sequenceNumber")==0) return base+1;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderID")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "size")==0) return base+4;
    if (fieldName[0]=='d' && strcmp(fieldName, "data")==0) return base+5;
    if (fieldName[0]=='i' && strcmp(fieldName, "isD2D")==0) return base+6;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *Data_packet2Descriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",
        "int",
        "int",
        "int",
        "int",
        "payload",
        "bool",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : nullptr;
}

const char **Data_packet2Descriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *Data_packet2Descriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int Data_packet2Descriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Data_packet2 *pp = (Data_packet2 *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *Data_packet2Descriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Data_packet2 *pp = (Data_packet2 *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Data_packet2Descriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Data_packet2 *pp = (Data_packet2 *)object; (void)pp;
    switch (field) {
        case 0: return bool2string(pp->getIsRequest());
        case 1: return long2string(pp->getSequenceNumber());
        case 2: return long2string(pp->getType());
        case 3: return long2string(pp->getSenderID());
        case 4: return long2string(pp->getSize());
        case 5: {std::stringstream out; out << pp->getData(); return out.str();}
        case 6: return bool2string(pp->getIsD2D());
        default: return "";
    }
}

bool Data_packet2Descriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Data_packet2 *pp = (Data_packet2 *)object; (void)pp;
    switch (field) {
        case 0: pp->setIsRequest(string2bool(value)); return true;
        case 1: pp->setSequenceNumber(string2long(value)); return true;
        case 2: pp->setType(string2long(value)); return true;
        case 3: pp->setSenderID(string2long(value)); return true;
        case 4: pp->setSize(string2long(value)); return true;
        case 6: pp->setIsD2D(string2bool(value)); return true;
        default: return false;
    }
}

const char *Data_packet2Descriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 5: return omnetpp::opp_typename(typeid(payload));
        default: return nullptr;
    };
}

void *Data_packet2Descriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Data_packet2 *pp = (Data_packet2 *)object; (void)pp;
    switch (field) {
        case 5: return (void *)(&pp->getData()); break;
        default: return nullptr;
    }
}


