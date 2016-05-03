//==============================================================================

#include "MainComponent.h"

//==============================================================================

void LabelImproved::focusGained (FocusChangeType cause)
{
    if (isEditable()
        && isEnabled()
        && cause == focusChangedByTabKey)
        showEditor();
}

//==============================================================================

List::List (List::EditOn editOn)
{
    switch (editOn)
    {
        case List::EditOn::singleClick :
            message.setText("Current tab traversal behaviour for single "
                            "click editable Labels:"
                            , NotificationType::dontSendNotification);
            break;
        case List::EditOn::doubleClick :
            message.setText("Current (unexpected?) tab traversal behaviour "
                            "for double click editable Labels:\n\n"
                            "void focusGained (FocusChangeType cause)\n"
                            "{\n"
                            "    if (editSingleClick\n"
                            "        && isEnabled()\n"
                            "        && cause == focusChangedByTabKey)\n"
                            "        showEditor();\n"
                            "}"
                            , NotificationType::dontSendNotification);
            break;
        case List::EditOn::doubleClickWithTraversing :
            message.setText("Suggested tab traversal behaviour for double "
                            "click editable Labels:\n\n"
                            "void focusGained (FocusChangeType cause)\n"
                            "{\n"
                            "    if (isEditable()\n"
                            "        && isEnabled()\n"
                            "        && cause == focusChangedByTabKey)\n"
                            "        showEditor();\n"
                            "}\n\n"
                            "...see https://forum.juce.com/t/17561"
                            , NotificationType::dontSendNotification);
            break;
        default :
            // Lists MUST be initialized with a valid List::EditOn argument!
            jassert (false);
    }
    
    message.setJustificationType (Justification::topLeft);
    message.setMinimumHorizontalScale (1.0f);
    message.setBorderSize (BorderSize<int> (10));
    message.setColour (Label::ColourIds::textColourId, Colours::white);
    addAndMakeVisible (message);
    
    for (int i = 0; i < 8; i++)
    {
        rows.add (new ListRow (editOn));
        addAndMakeVisible (rows[i]);
    }
    
    setFocusContainer (true);
    positionRows();
}

List::~List()
{
}

void List::positionRows()
{
    if (! rows.isEmpty())
    {
        Rectangle<int> rowsArea = getLocalBounds();
        message.setBounds (rowsArea.removeFromTop (200));
        rowsArea = rowsArea.reduced (2).withTrimmedBottom (-2);
        
        const int singleRowlHeight = rowsArea.getHeight() / rows.size();
        for (int i = 0; i < rows.size(); i++)
        {
            Rectangle<int> singleRowArea = rowsArea.removeFromTop (singleRowlHeight)
            .withTrimmedBottom (2);
            rows[i]->setBounds (singleRowArea);
        }
    }
}

void List::paint (Graphics& g)
{
    g.setColour (Colours::darkgrey);
    g.fillAll();
}

void List::resized()
{
    positionRows();
}

//==============================================================================

ListRow::ListRow (List::EditOn editOn)
{
    switch (editOn)
    {
        case List::EditOn::singleClick :
            label = new Label();
            label->setEditable (true, false);
            break;
        case List::EditOn::doubleClick :
            label = new Label();
            label->setEditable (false, true);
            break;
        case List::EditOn::doubleClickWithTraversing :
            label = new LabelImproved();
            label->setEditable (false, true);
            break;
        default :
            // ListRows MUST be initialized with a valid List::EditOn argument!
            jassert (false);
    }
    
    if (label->isEditableOnSingleClick())
        label->setText ("Edit me on single click...", NotificationType::dontSendNotification);
    else if (label->isEditableOnDoubleClick())
        label->setText ("Edit me on double click...", NotificationType::dontSendNotification);
    
    addAndMakeVisible (label);
}

ListRow::~ListRow()
{
}

void ListRow::paint (Graphics& g)
{
    g.setColour (Colours::white);
    g.fillAll();
}

void ListRow::resized()
{
    Rectangle<int> r = getLocalBounds();
    label->setBounds (r);
}

//==============================================================================

MainContentComponent::MainContentComponent()
{
    setSize (940, 470);
    
    for (int i = 0; i < 3; i++)
    {
        lists.add (new List (List::EditOn (i)));
        addAndMakeVisible (lists[i]);
    }
    
    positionLists();
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::positionLists()
{
    if (! lists.isEmpty())
    {
        Rectangle<int> r = getLocalBounds().reduced (10);
        int listWidth = r.getWidth() / lists.size();
        for (int i = 0; i < lists.size(); i++)
        {
            lists[i]->setBounds (r.removeFromLeft (listWidth).reduced (8));
        }
    }
}

void MainContentComponent::paint (Graphics& g)
{
    g.setColour (Colours::black);
    g.fillAll();
}

void MainContentComponent::resized()
{
    positionLists();
}
