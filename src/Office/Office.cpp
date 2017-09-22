#include "../../includes/Office/OfficeClerk.h"
#include "../../includes/System/ResourceLoader.h"
#include "../../includes/System/EntityContainer.h"
#include "../../includes/Office/Office.h"
#include "../../includes/Objects/Ground.h"

bool Office::hasNeighborOffice() {
    auto offices = EntityContainer::getOffices();

    for (auto office:offices) {
        if (office != this) {

            if (
                    office->getLeft() == this->right ||
                    office->getRight() == this->left
                    ) {
                return true;
            }


        }
    }


    return false;
}
