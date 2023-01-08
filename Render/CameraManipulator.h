#pragma once

#include <vsg/vsg.all>

class CameraManipulator : public vsg::Inherit<vsg::Visitor, CameraManipulator>
{
public:
	explicit CameraManipulator(vsg::ref_ptr<vsg::Camera> camera);

	/// compute non dimensional window coordinate (-1,1) from event coords
	vsg::dvec2 ndc(vsg::PointerEvent& event);

	/// compute trackball coordinate from event coords
	vsg::dvec3 tbc(vsg::PointerEvent& event);

	void apply(vsg::KeyPressEvent& keyPress) override;
	void apply(vsg::ButtonPressEvent& buttonPress) override;
	void apply(vsg::ButtonReleaseEvent& buttonRelease) override;
	void apply(vsg::MoveEvent& moveEvent) override;
	void apply(vsg::ScrollWheelEvent& scrollWheel) override;
	void apply(vsg::TouchDownEvent& touchDown) override;
	void apply(vsg::TouchUpEvent& touchUp) override;
	void apply(vsg::TouchMoveEvent& touchMove) override;
	void apply(vsg::FrameEvent& frame) override;

	virtual void rotate(double angle, const dvec3& axis);
	virtual void zoom(double ratio);
	virtual void pan(const dvec2& delta);

	std::pair<int32_t, int32_t> cameraRenderAreaCoordinates(const vsg::PointerEvent& pointerEvent) const;
	bool withinRenderArea(const vsg::PointerEvent& pointerEvent) const;

	void clampToGlobe();

	/// list of windows that this CameraManipulator should respond to events from, and the points xy offsets to apply
	std::map<vsg::observer_ptr<vsg::Window>, ivec2> windowOffsets;

	/// add a Window to respond events for, with mouse coordinate offset to treat all associated windows
	void addWindow(ref_ptr<vsg::Window> window, const ivec2& offset = {});

	/// add Key to Viewpoint binding using a LookAt to define the viewpoint
	void addKeyViewpoint(vsg::KeySymbol key, vsg::ref_ptr<vsg::LookAt> lookAt, double duration = 1.0);

	/// add Key to Viewpoint binding using a latitude, longitude and altitude to define the viewpoint. Requires an EllipsoidModel to be assigned when constructing the CameraManipulator
	void addKeyViewpoint(vsg::KeySymbol key, double latitude, double longitude, double altitude, double duration = 1.0);

	/// set the LookAt viewport to the specified lookAt, animating the movements from the current lookAt to the new one.
	/// A value of 0.0 instantly moves the lookAt to the new value.
	void setViewpoint(vsg::ref_ptr<vsg::LookAt> lookAt, double duration = 1.0);

	struct Viewpoint
	{
		vsg::ref_ptr<vsg::LookAt> lookAt;
		double duration = 0.0;
	};

	/// container that maps key symbol bindings with the Viewpoint that should move the LookAt to when pressed.
	std::map<vsg::KeySymbol, vsg::Viewpoint> keyViewpoitMap;

	/// Button mask value used to enable panning of the view, defaults to left mouse button
	vsg::ButtonMask rotateButtonMask = BUTTON_MASK_1;

	/// Button mask value used to enable panning of the view, defaults to middle mouse button
	vsg::ButtonMask panButtonMask = BUTTON_MASK_2;

	/// Button mask value used to enable zooming of the view, defaults to right mouse button
	vsg::ButtonMask zoomButtonMask = BUTTON_MASK_3;

	/// Scale for control how rapidly the view zooms in/out. Positive value zooms in when mouse moved downwards
	double zoomScale = 1.0;

	/// Toggle on/off whether the view should continue moving when the mouse buttons are released while the mouse is in motion.
	bool supportsThrow = true;

protected:
	vsg::ref_ptr<vsg::Camera> _camera;
	vsg::ref_ptr<vsg::LookAt> _lookAt;
	vsg::ref_ptr<vsg::EllipsoidModel> _ellipsoidModel;

	bool _hasFocus = false;
	bool _lastPointerEventWithinRenderArea = false;

	enum UpdateMode
	{
		INACTIVE = 0,
		ROTATE,
		PAN,
		ZOOM
	};
	UpdateMode _updateMode = INACTIVE;
	double _zoomPreviousRatio = 0.0;
	vsg::dvec2 _pan;
	double _rotateAngle = 0.0;
	vsg::dvec3 _rotateAxis;

	vsg::time_point _previousTime;
	vsg::ref_ptr<vsg::PointerEvent> _previousPointerEvent;
	double _previousDelta = 0.0;
	double _prevZoomTouchDistance = 0.0;
	bool _thrown = false;

	vsg::time_point _startTime;
	vsg::ref_ptr<vsg::LookAt> _startLookAt;
	vsg::ref_ptr<vsg::LookAt> _endLookAt;
	std::map<uint32_t, vsg::ref_ptr<vsg::TouchEvent>> _previousTouches;

	double _animationDuration = 0.0;
};
