#ifndef ATTRIBUTEMACROS_H_INCLUDED
#define ATTRIBUTEMACROS_H_INCLUDED

#ifdef className
#undef className
#endif
#define className boidsBrain
/*
#define RULEATTRIBUTESLENGTH 7
static const char * ruleAttributes[] = { "Active", "Priority", "Visibility", "AngleOfView", "Radius", "Factor", "Weight"};
static const char * ruleAttributesShort[] = { "a", "p", "v", "av", "r", "f", "w"};
static const char * ruleAttributesType[] = { kInt, kDouble, kDouble, kDouble, kDouble, kDouble, kDouble};
for(int i=0; i<RULEATTRIBUTESLENGTH; i++)
{
	declareAttr(_rule##ruleAttributes[i])
};	
*/

// boidsBrain.h
// class attribute declaration
#define setRuleAttributes(_rule)			\
	static MObject	_rule##Active;			\
	static MObject	_rule##Priority;		\
	static MObject	_rule##Visibility;		\
	static MObject	_rule##AngleOfView;		\
	static MObject	_rule##Radius;			\
	static MObject	_rule##Factor;			\
	static MObject	_rule##Weight;			\


// boidsBrain.cpp
// attribute assignment macros
#define declareAttr(_attr)			\
	MObject	className##::##_attr;	\

#define nodeAddAttribute(_attr)		\
	status = addAttribute( _attr );	\
	if (!status) { status.perror("addAttribute "#_attr); return status;} \

#define nodeCreateAttrNum(_name, _shortname, _type, _value) \
	_name = nAttr.create( #_name, #_shortname, MFnNumericData::##_type, _value); \
	nodeAddAttribute( _name ); \

#define nodeCreateAttrTyp(_name, _shortname) \
	_name = tAttr.create( #_name, #_shortname, MFnData::kString, &status ); \
	nodeAddAttribute( _name ); \

#define nodeCreateAttrMess(_name, _shortname) \
	_name = mAttr.create( #_name, #_shortname); \
	nodeAddAttribute( _name ); \


#define declareRuleAttributes(_rule)	\
	declareAttr(_rule##Active)			\
	declareAttr(_rule##Priority)		\
	declareAttr(_rule##Radius)			\
	declareAttr(_rule##Visibility)		\
	declareAttr(_rule##AngleOfView)		\
	declareAttr(_rule##Factor)			\
	declareAttr(_rule##Weight)			\

#define nodeCreateRuleAttributes(_rule, _r) \
	nodeCreateAttrNum(_rule##Active, _r##a, kBoolean, 1)				\
	nodeCreateAttrNum(_rule##Priority, _r##p, kDouble, 1)				\
	nodeCreateAttrNum(_rule##Radius, _r##r, kDouble, BDZ_DIST)			\
	nodeCreateAttrNum(_rule##Visibility, _r##v, kBoolean, 0)			\
	nodeCreateAttrNum(_rule##AngleOfView, _r##av, kDouble, 10)			\
	nodeCreateAttrNum(_rule##Factor, _r##f, kDouble, BDZ_SEPARATION)	\
	nodeCreateAttrNum(_rule##Weight, _r##w, kDouble, 1)					\

// simCmd.cpp
// declaring variables
#define setRuleVariables(_rule)				\
	int	_rule##ActiveValue;					\
	double	_rule##PriorityValue;			\
	double	_rule##RadiusValue;				\
	int	_rule##VisibilityValue;				\
	double	_rule##AngleOfViewValue;		\
	double	_rule##FactorValue;				\
	double	_rule##WeightValue;				\

// macro for getting values
#define getPlugValue(_attr)			\
	plug = nodeFn.findPlug( #_attr );	\
	plug.getValue( _attr##Value );	\
	cout << #_attr " is: " << ("%f", _attr##Value) << endl;	\

#define getTypePlugValue(_attr)			\
	plug = nodeFn.findPlug( #_attr );	\
	plug.getValue( _attr##Value );		\
	cout << #_attr " is: " << _attr##Value.asChar() << endl;	\

#define getRulePlugValue(_rule)			\
	getPlugValue(_rule##Active)			\
	getPlugValue(_rule##Priority)		\
	getPlugValue(_rule##Visibility)		\
	getPlugValue(_rule##AngleOfView)	\
	getPlugValue(_rule##Radius)			\
	getPlugValue(_rule##Factor)			\
	getPlugValue(_rule##Weight)			\

#endif