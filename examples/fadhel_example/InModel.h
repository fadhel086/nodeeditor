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

class InModel : public NodeDataModel
{
  //Q_OBJECT
  
 public:
  InModel()
    : _lineEdit(new QLineEdit())
    {
      _lineEdit->setMaximumSize(_lineEdit->sizeHint());
      connect(_lineEdit, &QLineEdit::textChanged, this, &InModel::textChanged);
      _lineEdit->setText("Enter Text");
    }
  
  ~InModel() {};

  void textChanged(void)
  {
    _data = _lineEdit->text();
    Q_EMIT dataUpdated(0);  // Hopefully emits the data
  }
  
  QString caption() const override
  {
    return QString("Input string");
  }

  QString name() const override
  {
    return QString("In string in CAPS");
  }

  unsigned int nPorts(PortType portType) const override
  {
    unsigned int result = 1;

    switch (portType)
    {
      case PortType::In:
      result = 0;
      break;

      case PortType::Out:
      result = 1;

      default:
      break;
    }

    return result;
  }

  NodeDataType dataType(PortType portType, PortIndex portIndex) const override
  {
    // Node out dataType {id, name}
    return StringData().type();
  }

  // Triggers the algorithm
  void setInData(std::shared_ptr<NodeData>, int) override
  {
    ;
  }

 std::shared_ptr<NodeData> outData(PortIndex port) override
 {
   return std::make_shared<StringData>(_data);
 }

  bool eventFilter(QObject *object, QEvent *event)
  {
    // No event
    return true;
  }

  QWidget* embeddedWidget() override {return _lineEdit;}

  bool resizable() const override {return true;}
  
 private:
  QLineEdit *_lineEdit;
  QString _data;
};
