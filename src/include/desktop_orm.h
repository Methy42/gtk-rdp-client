#ifndef DESKTOP_ORM_H
#define DESKTOP_ORM_H

#include <vector>
#include "desktop.h"

class DesktopORM {
public:
    DesktopORM();

    const std::vector<Desktop>& getDesktops() const;
    const Desktop& getDesktopById(int id) const;

    void addDesktop(const Desktop& desktop);
    bool updateDesktopById(int id, const Desktop& desktop);
    bool removeDesktopById(int id);

    static DesktopORM& getInstance();

private:
    static DesktopORM instance;
    std::string file_path_;
    std::vector<Desktop> desktops_;

    bool loadFromFile();
    bool saveToFile() const;
};

#endif  // DESKTOP_ORM_H
