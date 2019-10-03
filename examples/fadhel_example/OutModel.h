#pragma once

#include <iostream>
#include <QtWidgets/QLineEdit>

#include <nodes/DataModelRegistry>
#include <nodes/NodeDataModel>

#include "StringData.h"

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;


class OutModel : public NodeDataModel
{
  //Q_OBJECT
  
 public:
  OutModel()
    : _lineEdit(new QLineEdit())
    {
      _lineEdit->setMaximumSize(_lineEdit->sizeHint());
      _lineEdit->setText("");
    }
  
  ~OutModel() {};

  // Caption displayed in the GUI Node
  QString caption() const override
  {
    return QString("Output string");
  }

  // Name displayed upon left-click
  QString name() const override
  {
    return QString("Out string in small");
  }

  // Set the Input and output ports needed
  unsigned int nPorts(PortType portType) const override
  {
    unsigned int result = 1;

    switch (portType)
    {
      case PortType::In:
      result = 1;
      break;

      case PortType::Out:
      result = 0;

      default:
      break;
    }

    return result;
  }

  // Sets the Node Type as id and name appears in the GUI Node.
  NodeDataType dataType(PortType portType, PortIndex portIndex) const override
  {
    // Node out dataType {id, name}
    return StringData().type();
  }

  // Triggers the algorithm, for processing the received inputs
  void setInData(std::shared_ptr<NodeData> nodedata, int index) override
  {
    _nodeData = nodedata;

    if (_nodeData)
      {
	auto d = std::dynamic_pointer_cast<StringData>(_nodeData);
	_lineEdit->setText(StringData(*d).string().toLower());
      }
  }

  // Should be sending a pointer to next node, When Q_EMIT dataUpdated(port) is called.
  std::shared_ptr<NodeData> outData(PortIndex port) override
  {
    //return std::make_shared<StringData>(_data);
  }

  // Enters here on events, filter the events and do the required processing.
  bool eventFilter(QObject *object, QEvent *event)
  {
    // No event
    return true;
  }

  // Embed a Widget inside the Node.
  QWidget* embeddedWidget() override {return _lineEdit;}

  bool resizable() const override {return true;}
  
 private:
  QLineEdit *_lineEdit;
  QString _data;
  std::shared_ptr<NodeData> _nodeData;
};
