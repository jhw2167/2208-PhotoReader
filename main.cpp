/* Photo Reader main.cpp */
#include "Photo.h"

//Stubbs


//Global Vals
const unordered_set<string> VALID_TYPES{ ".png", ".jpg", ".jpeg" };

bool validFile(fs::path file) {
    string ext = boost::algorithm::to_lower_copy(file.extension().u8string());
    bool ext_exists = VALID_TYPES.find(ext)!=VALID_TYPES.end();
    return !fs::is_directory(file) && ext_exists;
}

int main()
{
    //Open a Directory with all images
    fs::path current = fs::current_path();
    fs::path path{ current.u8string() +"\\photos" };
    if (!fs::exists(path) || !fs::is_directory(path)) {
        //Exit
        string msg = string("") + "No 'photos' folder found, please add a folder " +
            "called " + path.u8string() + " with your images to the directory with " +
            "this program. ";
            cout << msg;
            return -1;
    }
    
    //Get list of all image names
    vector<string> files;
    for (const auto& entry : fs::directory_iterator(path))
    {
        fs::path filename = entry.path().filename();
        if (!validFile(filename)) {
            cout << "File: " << filename << " is not an image\n";
            continue;
        }
        
        
        //Open, read image, write image as JSON, next

        cout << filename << endl;
    }


    //close and exit

    return 0;
}




//Read .jpeg data
boolean readJpeg(fs::path path) {

    // open a stream to read just the necessary parts of the image file
    std::ifstream istream(path, std::ifstream::binary);

    // parse image EXIF and XMP metadata
    TinyEXIF::EXIFInfo imageEXIF(istream);
    if (imageEXIF.Fields) {
        Photo p = Photo(imageEXIF);
    }
    else {
        return false;
    }
    istream.close();
    
    return true;
}


//read .png data
boolean readPng(fs::path path) {
    sf::Image img;
    if (!img.loadFromFile(path.u8string())) {
        cout << "File: " << path << " could not be loaded\n";
        return false;
    }

    return true;
}