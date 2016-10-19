#include <fstream>
#include <string>
#include <libudev.h>
#include <iostream>

int open_file(std::string name, std::ifstream& fstream){
		fstream.open(name);
		if (fstream.is_open())
			return 1;
		else
			return 0;
}

int main (){

    struct udev *udev;
    struct udev_enumerate *enumerate;
    struct udev_list_entry *devices, *dev_list_entry;
    struct udev_device *dev;

    udev = udev_new();
    //udev = NULL;
    if (!udev) {
        throw "Can't creat udev\n";
    }

    /* Create a list of the disk devices in the 'block' subsystem. */
    //enumerate_scsi = udev_enumerate_new(udev);
    enumerate = udev_enumerate_new(udev);
    udev_enumerate_add_match_property(enumerate, "DRIVER", "sd");
    //udev_enumerate_add_match_property(enumerate, "UDISKS_PARTITION", "1");
    //UDev_enumerate_add_match_property(enumerate, "DEVTYPE", "disk");
    //udev_enumerate_add_match_subsystem(enumerate, "block");
    //udev_enumerate_add_match_subsystem(enumerate, "block");
    udev_enumerate_scan_devices(enumerate);
    devices = udev_enumerate_get_list_entry(enumerate);
    


    udev_list_entry_foreach(dev_list_entry, devices) {
        const char *path;
        
        /* Get the filename of the /sys entry for the device
           and create a udev_device object (dev) representing it */
        path = udev_list_entry_get_name(dev_list_entry);
        dev = udev_device_new_from_syspath(udev, path);

        /* usb_device_get_devnode() returns the path to the device node
           itself in /dev. */
        printf("Device Node Path: %s\n", udev_device_get_devnode(dev));

        /* The device pointed to by dev contains information about
           the hidraw device. In order to get information about the
           USB device, get the parent device with the
           subsystem/devtype pair of "usb"/"usb_device". This will
           be several levels up the tree, but the function will find
           it.*/
        /*dev = udev_device_get_parent_with_subsystem_devtype(
               dev,
               "scsi", NULL);*/
        if (!dev) {
            printf("Unable to find parent usb device.");
            //continue;
           // exit(1);
        }
    
        /* From here, we can call get_sysattr_value() for each file
           in the device's /sys entry. The strings passed into these
           functions (idProduct, idVendor, serial, etc.) correspond
           directly to the files in the directory which represents
           the USB device. Note that USB strings are Unicode, UCS2
           encoded, but the strings returned from
           udev_device_get_sysattr_value() are UTF-8 encoded. */
        printf("  model/PID: %s %s\n",
                udev_device_get_sysattr_value(dev,"model"),
                udev_device_get_property_value(dev, "SUBSYSTEM"));
        printf("%s  %s\n  %s\n",
                udev_device_get_sysattr_value(dev,"ID_BUS"),
                udev_device_get_property_value(dev,"DEVTYPE"),
                udev_device_get_property_value(dev,"ID_BUS"));
                //udev_device_get_sysattr_value(dev,"product"));
        printf("size (512B blocks): %s\n",
                 udev_device_get_sysattr_value(dev, "serial"));
        udev_device_unref(dev);
    }
    /* Free the enumerator object */
    udev_enumerate_unref(enumerate);

    udev_unref(udev);
/*
    std::ifstream meminfo_file;
    std::string line;
    std::string memsize;
	if (open_file("/proc/meminfo", meminfo_file)) {
		const std::string key = "MemTotal:";
		std::size_t found;

		while (getline(meminfo_file, line)) {
			found = line.find(key);
			if (found!=std::string::npos) {
                std::string value = line.substr(found+key.length(), line.length()-(found+key.length()+3));
                remove_copy(value.begin(), value.end(), std::back_inserter(memsize), ' ');
                std::cout << memsize << std::endl;
			}
		}
	}


    std::cout << "unknown" << std::endl;
*/
}
