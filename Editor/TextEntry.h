#pragma once

#include <vsg/all.h>

#include <semaphore>

#include "DirectoryEntry.h"

class AsyncQueue;

enum class TextHorizontalAlignment { Left, Center, Right };

enum class TextVerticalAlignment { Bottom, Center, Top };

class TextEntry : public Entry {
   public:
    TextEntry();
    TextEntry(const TextEntry& entry);

    EntryType GetType() const override;

    virtual void SetFont(const std::string& fontName);
    virtual std::string GetFont() const { return _fontName; }

    virtual void SetValue(const std::u8string& value);
    virtual std::u8string GetValue() const { return _value; }

    virtual double GetOffsetX() const { return _offset[0]; }
    virtual double GetOffsetY() const { return _offset[1]; }
    virtual double GetOffsetZ() const { return _offset[2]; }

    virtual double GetHorizontalAxisX() const { return _horAxis[0]; }
    virtual double GetHorizontalAxisY() const { return _horAxis[1]; }
    virtual double GetHorizontalAxisZ() const { return _horAxis[2]; }

    virtual double GetVerticalAxisX() const { return _vertAxis[0]; }
    virtual double GetVerticalAxisY() const { return _vertAxis[1]; }
    virtual double GetVerticalAxisZ() const { return _vertAxis[2]; }

    virtual double GetColorR() const { return _color[0]; }
    virtual double GetColorG() const { return _color[1]; }
    virtual double GetColorB() const { return _color[2]; }
    virtual double GetColorA() const { return _color[3]; }

    virtual TextHorizontalAlignment GetHorizontalAlignment() const {
        return _horAlignment;
    }
    virtual TextVerticalAlignment GetVerticalAlignment() const {
        return _vertAlignment;
    }

    virtual double GetLineSpacing() const { return _lineSpacing; }

    virtual void SetOffsetX(double value);
    virtual void SetOffsetY(double value);
    virtual void SetOffsetZ(double value);

    virtual void SetHorizontalAxisX(double value);
    virtual void SetHorizontalAxisY(double value);
    virtual void SetHorizontalAxisZ(double value);

    virtual void SetVerticalAxisX(double value);
    virtual void SetVerticalAxisY(double value);
    virtual void SetVerticalAxisZ(double value);

    virtual void SetColor(double r, double g, double b, double a);
    virtual void SetColorR(double value);
    virtual void SetColorG(double value);
    virtual void SetColorB(double value);
    virtual void SetColorA(double value);

    virtual void SetHorizontalAlignment(TextHorizontalAlignment value);
    virtual void SetVerticalAlignment(TextVerticalAlignment value);
    virtual void SetLineSpacing(double value);

    std::shared_ptr<Entry> CreateProxy(EntryPath path) override;
    std::shared_ptr<Entry> FindEntry(const EntryPath&) const { return {}; }

    void Serialize(EntryProperties& properties) const override;
    void DeserializeInternal(EntryPath path,
                             const EntryProperties& properties) override;

   protected:
    std::shared_ptr<Entry> CreateView(
        std::shared_ptr<AsyncQueue> sync) override;
    void CloneFrom(std::shared_ptr<Entry> entry) override;
    std::shared_ptr<Entry> CreateCopy() const override;

   private:
    std::string _fontName;
    std::u8string _value;

    std::array<double, 3> _offset{0, 0, 0};
    std::array<double, 3> _horAxis{1, 0, 0};
    std::array<double, 3> _vertAxis{0, 0, 1};
    std::array<double, 4> _color{0, 0, 0, 1};

    TextHorizontalAlignment _horAlignment{TextHorizontalAlignment::Center};
    TextVerticalAlignment _vertAlignment{TextVerticalAlignment::Center};

    double _lineSpacing{1.0};
};

class TextEntryView : public TextEntry {
   public:
    TextEntryView(std::shared_ptr<TextEntry> dataModel,
                  std::shared_ptr<AsyncQueue> syncContext)
        : _model{dataModel}, _sync{syncContext} {
        SetParent(dataModel->GetParent());
    }

    TextEntryView() {}

    std::shared_ptr<Entry> CreateProxy(EntryPath path) override;

    void SetFont(const std::string& fontName) override;
    std::string GetFont() const override;

    void SetValue(const std::u8string& value) override;
    std::u8string GetValue() const override;

    void Serialize(EntryProperties& properties) const override;
    void DeserializeInternal(EntryPath path,
                             const EntryProperties& properties) override;

    double GetOffsetX() const override;
    double GetOffsetY() const override;
    double GetOffsetZ() const override;

    double GetHorizontalAxisX() const override;
    double GetHorizontalAxisY() const override;
    double GetHorizontalAxisZ() const override;

    double GetVerticalAxisX() const override;
    double GetVerticalAxisY() const override;
    double GetVerticalAxisZ() const override;

    double GetColorR() const override;
    double GetColorG() const override;
    double GetColorB() const override;
    double GetColorA() const override;

    TextHorizontalAlignment GetHorizontalAlignment() const override;
    TextVerticalAlignment GetVerticalAlignment() const override;

    double GetLineSpacing() const override;

    void SetOffsetX(double value) override;
    void SetOffsetY(double value) override;
    void SetOffsetZ(double value) override;

    void SetHorizontalAxisX(double value) override;
    void SetHorizontalAxisY(double value) override;
    void SetHorizontalAxisZ(double value) override;

    void SetVerticalAxisX(double value) override;
    void SetVerticalAxisY(double value) override;
    void SetVerticalAxisZ(double value) override;

    void SetColor(double r, double g, double b, double a) override;
    void SetColorR(double value) override;
    void SetColorG(double value) override;
    void SetColorB(double value) override;
    void SetColorA(double value) override;

    void SetHorizontalAlignment(TextHorizontalAlignment value) override;
    void SetVerticalAlignment(TextVerticalAlignment value) override;
    void SetLineSpacing(double value) override;

   protected:
    void CloneFrom(std::shared_ptr<Entry> entry) override;
    std::shared_ptr<Entry> CreateCopy() const override;

   private:
    std::shared_ptr<TextEntry> _model;
    std::shared_ptr<AsyncQueue> _sync;
};