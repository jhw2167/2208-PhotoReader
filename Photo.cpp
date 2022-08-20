#include "Photo.h"

//Useful methods
string toString(double x) {
	return boost::str(boost::format("%.2f") % x);
}

CameraDetails::CameraDetails() {
}

CameraDetails::CameraDetails(TinyEXIF::EXIFInfo exif) {
	setJpegValues(exif);
}

void CameraDetails::setJpegValues(TinyEXIF::EXIFInfo exif) {
	aperture = toString(exif.ApertureValue);
	exposure = toString(exif.ExposureTime);
	focalLength = toString(exif.FocalLength);
	lens = exif.LensInfo.Make + " " + exif.LensInfo.Model;
	shutterSpeed = toString(exif.ShutterSpeedValue);
	make = exif.Make;
	model = exif.Model;
}


Photo::Photo(){
}

Photo::Photo(TinyEXIF::EXIFInfo exif) {
	setJpegValues(exif);
}

Photo::Photo(sf::Image img){
	setPngValues(img);
}

//Photo Class
void Photo::setJpegValues(TinyEXIF::EXIFInfo exif) {

	TinyEXIF::EXIFInfo::Geolocation_t loc = exif.GeoLocation;

	description = exif.ImageDescription;
	resolution = toString(exif.ImageWidth) + "x" 
		+ toString(exif.ImageHeight);
	if (loc.hasLatLon())
		location = toString(loc.Latitude) + "," +
		toString(loc.Longitude);
	if(loc.hasAltitude())
		location += ","+toString(loc.Altitude);

	if(!exif.DateTime.empty())
		dateTime = exif.DateTime;
	else if(!exif.DateTimeOriginal.empty())
		dateTime = exif.DateTimeOriginal;
	else 
		dateTime = exif.DateTimeDigitized;

	details.setJpegValues(exif);
}

void Photo::setPngValues(sf::Image img) {
	resolution = toString(img.getSize().y) + "x" +
		toString(img.getSize().x);
}

void Photo::setTitle(string t) {
	title = t;
}