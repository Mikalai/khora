#include "TransformPanel.h"
#include "../Application.h"

#include "../TransformEntry.h"

namespace Vandrouka {
TransformPanel::TransformPanel(wxWindow *parent) : TransformPanelBase(parent) {
  
    _observerWrapper = new ObserverWrapper{this};
  _sinkWrapper = new MessageSinkWrapper{this};
  _stateWrapper = new TransformPanelStateWrapper{this};
  _processor = Application::CreateWxProcessor();

  _matrix[0][0] = this->txt00;
  _matrix[0][1] = this->txt01;
  _matrix[0][2] = this->txt02;
  _matrix[0][3] = this->txt03;

  _matrix[1][0] = this->txt10;
  _matrix[1][1] = this->txt11;
  _matrix[1][2] = this->txt12;
  _matrix[1][3] = this->txt13;

  _matrix[2][0] = this->txt20;
  _matrix[2][1] = this->txt21;
  _matrix[2][2] = this->txt22;
  _matrix[2][3] = this->txt23;

  _matrix[3][0] = this->txt30;
  _matrix[3][1] = this->txt31;
  _matrix[3][2] = this->txt32;
  _matrix[3][3] = this->txt33;

  _position[0] = this->posTxt0;
  _position[1] = this->posTxt1;
  _position[2] = this->posTxt2;

  _scale[0] = this->scaleTxt0;
  _scale[1] = this->scaleTxt1;
  _scale[2] = this->scaleTxt2;

  _orientation[0] = this->orient0;
  _orientation[1] = this->orient1;
  _orientation[2] = this->orient2;
  _orientation[3] = this->orient3;
}

void TransformPanel::SetDataModel(Vandrouka::Ref<IEntry> entry) {
  _dataModelSubscription.Reset();

  _dataModel = entry.Cast<ITransformEntry>();

  if (auto o = _dataModel.Cast<IObservable>(); o) {
    _dataModelSubscription = o->Subscribe(_observerWrapper);
  }

  if (_dataModel) {
    UpdateControls();
    this->Show(true);
  } else {
    this->Show(false);
  }
}

void TransformPanel::UpdateControls() {
  if (!_dataModel)
    return;

  this->overrideCheckBox->Set3StateValue(
      _dataModel->GetOverride() ? wxCHK_CHECKED : wxCHK_UNCHECKED);
  const auto pos = _dataModel->GetPosition();
  for (int i = 0; i < 3; ++i) {
    this->_position[i]->SetValue(std::to_string(pos[i]));
  }

  const auto orient = _dataModel->GetOrientation();
  for (int i = 0; i < 4; ++i) {
    this->_orientation[i]->SetValue(std::to_string(orient[i]));
  }

  const auto scale = _dataModel->GetScale();
  for (int i = 0; i < 3; ++i) {
    this->_scale[i]->SetValue(std::to_string(scale[i]));
  }

  if (auto tr = _dataModel->GetTransform(); tr) {
    const auto trans = tr->matrix;
    for (int r = 0; r < 4; ++r) {
      for (int c = 0; c < 4; ++c) {
        this->_matrix[r][c]->SetValue(std::to_string(trans[r][c]));
      }
    }
  }
}

void TransformPanel::AddRef() {}

void TransformPanel::Release() {}

bool TransformPanel::QueryInterface(const InterfaceId &id, void **o) {
  return false;
}

void TransformPanel::OnNext(Vandrouka::Ref<IMessage> msg) {
  _processor->Process(_stateWrapper, msg, _sinkWrapper);
}

void TransformPanel::OnError(Vandrouka::Ref<IError> error) {}

void TransformPanel::OnComplete() {}

void TransformPanel::SubmitMessage(Vandrouka::Ref<IMessage> msg) {}

void TransformPanel::SubmitError(Vandrouka::Ref<IError> msg) {}

void TransformPanel::matrixValueChanged(wxCommandEvent &) {
  if (!_dataModel)
    return;
}

void TransformPanel::overrideChanged(wxCommandEvent &) {
  if (!_dataModel)
    return;

  _dataModel->SetOverride(this->overrideCheckBox->Get3StateValue() ==
                          wxCHK_CHECKED);
}

void TransformPanel::positionChanged(wxCommandEvent &event) {
  if (!_dataModel)
    return;

  for (int i = 0; i < 3; ++i) {
    if (_position[i] == event.GetEventObject()) {
      double value;
      if (_position[i]->GetValue().ToCDouble(&value)) {
        auto o = _dataModel->GetPosition();
        o[i] = value;
        _dataModel->SetPosition(o);
        return;
      }
    }
  }
}

void TransformPanel::scaleChanged(wxCommandEvent &event) {
  if (!_dataModel)
    return;

  for (int i = 0; i < 3; ++i) {
    if (_scale[i] == event.GetEventObject()) {
      double value;
      if (_scale[i]->GetValue().ToCDouble(&value)) {
        auto o = _dataModel->GetScale();
        o[i] = value;
        _dataModel->SetScale(o);
        return;
      }
    }
  }
}

void TransformPanel::orientationChanged(wxCommandEvent &event) {
  if (!_dataModel)
    return;

  for (int i = 0; i < 4; ++i) {
    if (_orientation[i] == event.GetEventObject()) {
      double value;
      if (_orientation[i]->GetValue().ToCDouble(&value)) {
        auto o = _dataModel->GetOrientation();
        o[i] = value;
        _dataModel->SetOrientation(o);
        return;
      }
    }
  }
}

void TransformPanel::copyPosXOnButtonClick(wxCommandEvent &) {
  _copyPosition[0] = _position[0]->GetValue();
}

void TransformPanel::pastePosXOnButtonClick(wxCommandEvent &) {
  _position[0]->SetValue(_copyPosition[0]);
}

void TransformPanel::copyPosYOnButtonClick(wxCommandEvent &) {
  _copyPosition[1] = _position[1]->GetValue();
}

void TransformPanel::pastePosYOnButtonClick(wxCommandEvent &) {
  _position[1]->SetValue(_copyPosition[1]);
}

void TransformPanel::copyPosZOnButtonClick(wxCommandEvent &) {
  _copyPosition[2] = _position[2]->GetValue();
}

void TransformPanel::pastePosZOnButtonClick(wxCommandEvent &) {
  _position[2]->SetValue(_copyPosition[2]);
}

void TransformPanel::pastePosOnButtonClick(wxCommandEvent &) {
  for (int i = 0; i < 3; ++i) {
    _position[i]->SetValue(_copyPosition[i]);
  }
}

void TransformPanel::copyPosOnButtonClick(wxCommandEvent &) {
  for (int i = 0; i < 3; ++i) {
    _copyPosition[i] = _position[i]->GetValue();
  }
}

void TransformPanel::copyScaleXOnButtonClick(wxCommandEvent &) {
  _scale[0]->SetValue(_copyScale[0]);
}

void TransformPanel::pasteScaleXOnButtonClick(wxCommandEvent &) {
  _scale[0]->SetValue(_copyScale[0]);
}

void TransformPanel::copyScaleYOnButtonClick(wxCommandEvent &) {
  _copyScale[1] = _scale[1]->GetValue();
}

void TransformPanel::pasteScaleYOnButtonClick(wxCommandEvent &) {
  _scale[1]->SetValue(_copyScale[1]);
}

void TransformPanel::copyScaleZOnButtonClick(wxCommandEvent &) {
  _copyScale[2] = _scale[2]->GetValue();
}

void TransformPanel::pasteScaleZOnButtonClick(wxCommandEvent &) {
  _scale[2]->SetValue(_copyScale[2]);
}

void TransformPanel::copyScaleOnButtonClick(wxCommandEvent &) {
  for (int i = 0; i < 3; ++i) {
    _copyScale[i] = _scale[i]->GetValue();
  }
}

void TransformPanel::pasteScaleOnButtonClick(wxCommandEvent &) {
  for (int i = 0; i < 3; ++i) {
    _scale[i]->SetValue(_copyScale[i]);
  }
}
} // namespace Vandrouka

//TransformPanel::TransformPanel(wxWindow *parent) : TransformPanelBase(parent) {
//  _matrix[0][0] = this->txt00;
//  _matrix[0][1] = this->txt01;
//  _matrix[0][2] = this->txt02;
//  _matrix[0][3] = this->txt03;
//
//  _matrix[1][0] = this->txt10;
//  _matrix[1][1] = this->txt11;
//  _matrix[1][2] = this->txt12;
//  _matrix[1][3] = this->txt13;
//
//  _matrix[2][0] = this->txt20;
//  _matrix[2][1] = this->txt21;
//  _matrix[2][2] = this->txt22;
//  _matrix[2][3] = this->txt23;
//
//  _matrix[3][0] = this->txt30;
//  _matrix[3][1] = this->txt31;
//  _matrix[3][2] = this->txt32;
//  _matrix[3][3] = this->txt33;
//
//  _position[0] = this->posTxt0;
//  _position[1] = this->posTxt1;
//  _position[2] = this->posTxt2;
//
//  _scale[0] = this->scaleTxt0;
//  _scale[1] = this->scaleTxt1;
//  _scale[2] = this->scaleTxt2;
//
//  _orientation[0] = this->orient0;
//  _orientation[1] = this->orient1;
//  _orientation[2] = this->orient2;
//  _orientation[3] = this->orient3;
//}
//
//void TransformPanel::SetDataModel(std::shared_ptr<Entry> entry) {
//  if (_dataModel) {
//    _dataModel->RemoveObserver(shared_from_this());
//  }
//
//  _dataModel = std::dynamic_pointer_cast<TransformEntry>(entry);
//
//  if (_dataModel) {
//    _dataModel->AddObserver(shared_from_this());
//    UpdateControls();
//    this->Show(true);
//  } else {
//    this->Show(false);
//  }
//}
//
//void TransformPanel::UpdateControls() {
//  if (!_dataModel)
//    return;
//
//  this->overrideCheckBox->Set3StateValue(
//      _dataModel->GetOverride() ? wxCHK_CHECKED : wxCHK_UNCHECKED);
//  const auto pos = _dataModel->GetPosition();
//  for (int i = 0; i < 3; ++i) {
//    this->_position[i]->SetValue(std::to_string(pos[i]));
//  }
//
//  const auto orient = _dataModel->GetOrientation();
//  for (int i = 0; i < 4; ++i) {
//    this->_orientation[i]->SetValue(std::to_string(orient[i]));
//  }
//
//  const auto scale = _dataModel->GetScale();
//  for (int i = 0; i < 3; ++i) {
//    this->_scale[i]->SetValue(std::to_string(scale[i]));
//  }
//
//  if (auto tr = _dataModel->GetTransform(); tr) {
//    const auto trans = tr->matrix;
//    for (int r = 0; r < 4; ++r) {
//      for (int c = 0; c < 4; ++c) {
//        this->_matrix[r][c]->SetValue(std::to_string(trans[r][c]));
//      }
//    }
//  }
//}
//
//void TransformPanel::OnEntryAdded(EntryPath, std::shared_ptr<Entry> entry) {
//  if (_dataModel != entry)
//    return;
//}
//
//void TransformPanel::OnEntryRemoved(EntryPath, std::shared_ptr<Entry> entry) {
//  if (_dataModel != entry)
//    return;
//}
//
//void TransformPanel::OnPropertyChanged(std::shared_ptr<Entry> sender,
//                                       std::string_view) {
//  if (_dataModel != sender)
//    return;
//}
//
//void TransformPanel::matrixValueChanged(wxCommandEvent &) {
//  if (!_dataModel)
//    return;
//}
//
//void TransformPanel::overrideChanged(wxCommandEvent &) {
//  if (!_dataModel)
//    return;
//
//  _dataModel->SetOverride(this->overrideCheckBox->Get3StateValue() ==
//                          wxCHK_CHECKED);
//}
//
//void TransformPanel::positionChanged(wxCommandEvent &event) {
//  if (!_dataModel)
//    return;
//
//  for (int i = 0; i < 3; ++i) {
//    if (_position[i] == event.GetEventObject()) {
//      double value;
//      if (_position[i]->GetValue().ToCDouble(&value)) {
//        auto o = _dataModel->GetPosition();
//        o[i] = value;
//        _dataModel->SetPosition(o);
//        return;
//      }
//    }
//  }
//}
//
//void TransformPanel::scaleChanged(wxCommandEvent &event) {
//  if (!_dataModel)
//    return;
//
//  for (int i = 0; i < 3; ++i) {
//    if (_scale[i] == event.GetEventObject()) {
//      double value;
//      if (_scale[i]->GetValue().ToCDouble(&value)) {
//        auto o = _dataModel->GetScale();
//        o[i] = value;
//        _dataModel->SetScale(o);
//        return;
//      }
//    }
//  }
//}
//
//void TransformPanel::orientationChanged(wxCommandEvent &event) {
//  if (!_dataModel)
//    return;
//
//  for (int i = 0; i < 4; ++i) {
//    if (_orientation[i] == event.GetEventObject()) {
//      double value;
//      if (_orientation[i]->GetValue().ToCDouble(&value)) {
//        auto o = _dataModel->GetOrientation();
//        o[i] = value;
//        _dataModel->SetOrientation(o);
//        return;
//      }
//    }
//  }
//}
//
//void TransformPanel::copyPosXOnButtonClick(wxCommandEvent &) {
//  _copyPosition[0] = _position[0]->GetValue();
//}
//
//void TransformPanel::pastePosXOnButtonClick(wxCommandEvent &) {
//  _position[0]->SetValue(_copyPosition[0]);
//}
//
//void TransformPanel::copyPosYOnButtonClick(wxCommandEvent &) {
//  _copyPosition[1] = _position[1]->GetValue();
//}
//
//void TransformPanel::pastePosYOnButtonClick(wxCommandEvent &) {
//  _position[1]->SetValue(_copyPosition[1]);
//}
//
//void TransformPanel::copyPosZOnButtonClick(wxCommandEvent &) {
//  _copyPosition[2] = _position[2]->GetValue();
//}
//
//void TransformPanel::pastePosZOnButtonClick(wxCommandEvent &) {
//  _position[2]->SetValue(_copyPosition[2]);
//}
//
//void TransformPanel::pastePosOnButtonClick(wxCommandEvent &) {
//  for (int i = 0; i < 3; ++i) {
//    _position[i]->SetValue(_copyPosition[i]);
//  }
//}
//
//void TransformPanel::copyPosOnButtonClick(wxCommandEvent &) {
//  for (int i = 0; i < 3; ++i) {
//    _copyPosition[i] = _position[i]->GetValue();
//  }
//}
//
//void TransformPanel::copyScaleXOnButtonClick(wxCommandEvent &) {
//  _scale[0]->SetValue(_copyScale[0]);
//}
//
//void TransformPanel::pasteScaleXOnButtonClick(wxCommandEvent &) {
//  _scale[0]->SetValue(_copyScale[0]);
//}
//
//void TransformPanel::copyScaleYOnButtonClick(wxCommandEvent &) {
//  _copyScale[1] = _scale[1]->GetValue();
//}
//
//void TransformPanel::pasteScaleYOnButtonClick(wxCommandEvent &) {
//  _scale[1]->SetValue(_copyScale[1]);
//}
//
//void TransformPanel::copyScaleZOnButtonClick(wxCommandEvent &) {
//  _copyScale[2] = _scale[2]->GetValue();
//}
//
//void TransformPanel::pasteScaleZOnButtonClick(wxCommandEvent &) {
//  _scale[2]->SetValue(_copyScale[2]);
//}
//
//void TransformPanel::copyScaleOnButtonClick(wxCommandEvent &) {
//  for (int i = 0; i < 3; ++i) {
//    _copyScale[i] = _scale[i]->GetValue();
//  }
//}
//
//void TransformPanel::pasteScaleOnButtonClick(wxCommandEvent &) {
//  for (int i = 0; i < 3; ++i) {
//    _scale[i]->SetValue(_copyScale[i]);
//  }
//}