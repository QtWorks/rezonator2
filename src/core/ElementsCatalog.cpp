#include "ElementsCatalog.h"
#include "Elements.h"

#include <QApplication>

ElementsCatalog::ElementsCatalog()
{
    auto categoryCommon = qApp->translate("Elements", "Common elements");
    registerElement(categoryCommon, new ElemEmptyRange);
    registerElement(categoryCommon, new ElemPlate);
    registerElement(categoryCommon, new ElemFlatMirror);
    registerElement(categoryCommon, new ElemCurveMirror);
    registerElement(categoryCommon, new ElemThinLens);
    registerElement(categoryCommon, new ElemTiltedCrystal);
    registerElement(categoryCommon, new ElemTiltedPlate);
    registerElement(categoryCommon, new ElemBrewsterCrystal);
    registerElement(categoryCommon, new ElemBrewsterPlate);

    auto categoryAux = qApp->translate("Elements", "Additional elements");
    registerElement(categoryAux, new ElemMatrix);
    registerElement(categoryAux, new ElemPoint);
    registerElement(categoryAux, new ElemThickLens);
    registerElement(categoryAux, new ElemCylinderLensT);
    registerElement(categoryAux, new ElemCylinderLensS);
    registerElement(categoryAux, new ElemGrinLens);
    registerElement(categoryAux, new ElemAxiconMirror);
    registerElement(categoryAux, new ElemAxiconLens);

    auto categoryIntf = qApp->translate("Elements", "Media and interfaces");
    registerElement(categoryIntf, new ElemMediumRange);
    registerElement(categoryIntf, new ElemNormalInterface);
    registerElement(categoryIntf, new ElemBrewsterInterface);
    registerElement(categoryIntf, new ElemTiltedInterface);
    registerElement(categoryIntf, new ElemSphericalInterface);
}

ElementsCatalog::~ElementsCatalog()
{
    qDeleteAll(_elements);
}

void ElementsCatalog::registerElement(const QString &category, Element *elem)
{
    foreach (Element *e, _elements)
        if (e->type() == elem->type())
            return;

    if (!_categories.contains(category))
        _categories.append(category);

    if (!_elements.contains(elem))
        _elements.append(elem);

    if (!_elemsCategorized[category].contains(elem))
        _elemsCategorized[category].append(elem);
}

Element* ElementsCatalog::create(const QString& type) const
{
    for (Element* maker : _elements)
        if (maker->type() == type)
        {
            auto elem = maker->create();
            elem->calcMatrix();
            return elem;
        }
    return nullptr;
}

Elements ElementsCatalog::elements(const QString& category) const
{
    return _elemsCategorized.contains(category)? _elemsCategorized[category]: Elements();
}
