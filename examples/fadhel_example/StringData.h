#ifndef STRING_DATA
#define STRING_DATA

#include <nodes/NodeDataModel>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

class StringData : public NodeData
{

 public:
  StringData() {};
  StringData(QString const &data)
    : _data(data) {}

  NodeDataType type() const override
  {
    return {"string", "str"};
  }

  QString string() const {return _data;}
  
private:
  QString _data;
};

#endif
