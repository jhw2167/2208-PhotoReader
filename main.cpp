/* Photo Reader main.cpp */
#include "main.h"

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
        
        sf::Image img;
        if (!img.loadFromFile(entry.path().string())) {
            cout << "File: " << filename << " could not be loaded\n";
            continue;
        }
    }

    //While list !empty, iterate
    while (!files.empty()) {

    }

    //Open, read image, write image as JSON, next

    //close and exit

    return 0;
}