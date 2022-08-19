#pragma once

#include "main.h"

class CameraDetails {

	private: 
		string aperture;
		string exposure;
		string focalLength;
		string lens;
		string shutterSpeed;
		string model;
		string make;

	public:
		CameraDetails();
		CameraDetails(TinyEXIF::EXIFInfo exif);
		void setJpegValues(TinyEXIF::EXIFInfo exif);

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(CameraDetails,
			aperture, exposure, focalLength, lens,
			shutterSpeed, model, make)
};

class Photo
{
	private:
		string title;
		string description;
		string resolution;
		string location;	//lattitude, longitude, altitude
		string dateTime;
		CameraDetails details;

	public:

		Photo();
		Photo(TinyEXIF::EXIFInfo exif);
		Photo(sf::Image img);

		//set values from jpg imageExif
		void setJpegValues(TinyEXIF::EXIFInfo exif);
		void setPngValues(sf::Image img);
		void setTitle(string title);

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Photo,
			title, description, resolution, location,
			dateTime, details)
};

