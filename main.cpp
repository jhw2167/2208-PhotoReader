/* Photo Reader main.cpp */
#include "Photo.h"

#define CHECK_FIELDS false
//Stubbs
boolean readJpeg(fs::path path, Photo& p);
boolean readPng(fs::path path, Photo& p);

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
            std::cout << msg;
            return -1;
    }
    
    //File writers
    std::filebuf fb;
    fb.open("out.json", std::ios::out);
    std::ostream os(&fb);
    char delim = '[';
    //Get list of all image names
    for (const auto& entry : fs::directory_iterator(path))
    {
        fs::path filename = entry.path().filename();
        if (!validFile(filename)) {
            std::cout << "File: " << filename << " is not an image\n";
            continue;
        }
        
        //Open, read image, write image as JSON, next
        string ext = boost::algorithm::to_lower_copy(filename.extension().u8string());
        
        Photo p = Photo();
        string name = filename.u8string();
        p.title = name.substr(0, name.find(".", 0));
        if (ext == ".png") {
            if (!readPng(entry, p)) {
                std::cout << "Error loading image: " << filename << endl;
                continue;
           }
        }
        else if (ext == ".jpeg" || ext == ".jpg") {
            if (!readJpeg(entry, p)) {
                std::cout << "Error loading image: " << filename << endl;
                continue;
            }
        }
        else {
            std::cout << "Unkown file extension: " << filename << endl;
            continue;
        }

        json j = p; 
        os << delim << j;
        std::cout << "Wrote out: " << filename << endl;
        delim = ',';
    }
    //close and exit
    os << ']';
    fb.close();

    return 0;
}




//Read .jpeg data
boolean readJpeg(fs::path path, Photo& p) {

    // open a stream to read just the necessary parts of the image file
    std::ifstream istream(path, std::ifstream::binary);

    // parse image EXIF and XMP metadata
    TinyEXIF::EXIFInfo imageEXIF(istream);
    if (imageEXIF.Fields)
        p.setJpegValues(imageEXIF);
    else
        return false;

    if(CHECK_FIELDS)
        std::cout
        << "Image Description " << imageEXIF.ImageDescription << "\n"
        << "Image Resolution " << imageEXIF.ImageWidth << "x" << imageEXIF.ImageHeight << " pixels\n"
        << "Camera Model " << imageEXIF.Make << " - " << imageEXIF.Model << "\n"
        << "Focal Length " << imageEXIF.FocalLength << " mm" << std::endl;

    istream.close();
    
    return true;
}


//read .png data
boolean readPng(fs::path path, Photo& p) {
    sf::Image img;
    if (!img.loadFromFile(path.u8string())) {
        std::cout << "File: " << path << " could not be loaded\n";
        return false;
    }
    p.setPngValues(img);
    return true;
}