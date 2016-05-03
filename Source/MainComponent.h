//==============================================================================

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================

struct ListRow;

//==============================================================================

class LabelImproved     : public Label
{
protected:
    void focusGained (FocusChangeType) override;
};

//==============================================================================

struct List             : public Component
{
    enum EditOn : unsigned int {
        singleClick,
        doubleClick,
        doubleClickWithTraversing,
        end
    };
    
    List (EditOn editOn);
    ~List();
    
    void positionRows();
    void paint (Graphics&) override;
    void resized() override;
    
private:
    EditOn editOn;
    Label message;
    OwnedArray<ListRow> rows;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (List)
};

//==============================================================================

struct ListRow          : public Component
{
    ListRow (List::EditOn editOn);
    ~ListRow();
    
    void paint (Graphics&) override;
    void resized() override;
    
    ScopedPointer<Label> label;
    
private:
    List::EditOn editOn;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ListRow)
};

//==============================================================================

class MainContentComponent   : public Component
{
public:
    MainContentComponent();
    ~MainContentComponent();

    void positionLists ();
    void paint (Graphics&);
    void resized();
    
    OwnedArray<List> lists;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
