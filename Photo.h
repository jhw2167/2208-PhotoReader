#pragma once

#include "main.h"

class CameraDetails {

	public:
		string aperture;
		string exposure;
		string focalLength;
		string lens;
		string shutterSpeed;
		string model;
		string make;

		CameraDetails();
		CameraDetails(TinyEXIF::EXIFInfo exif);
		void setJpegValues(TinyEXIF::EXIFInfo exif);

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(CameraDetails,
			aperture, exposure, focalLength, lens,
			shutterSpeed, model, make)
};

class Photo
{
	public:
		string filename;
		string title;
		string description;
		string resolution;
		string location;	//lattitude, longitude, altitude
		string friendlyLocation;
		string dateTime;
		string orientation;
		CameraDetails details;

		Photo();
		Photo(TinyEXIF::EXIFInfo exif);
		Photo(sf::Image img);

		//set values from jpg imageExif
		void setJpegValues(TinyEXIF::EXIFInfo exif);
		void setPngValues(sf::Image img);
		void setTitle(string title);

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Photo, filename,
			title, description, resolution, location, friendlyLocation,
			dateTime, orientation, details)
};

