#include <vector>

class OBJECT_BASE_SURFACE {
    private:
        std::vector<float> reflexion_coefficient;
        std::vector<float> transmission_coefficient;
        std::vector<float> absorption_coefficient;

    public:
        void getColors(
            std::vector<int>& incident,
            std::vector<int>& reflected,
            std::vector<int>& transmitted,
            std::vector<int>& absorbed
        );

        /** Constructors */
        OBJECT_BASE_SURFACE() {
            for (int i = 0; i < 3; i++) {
                reflexion_coefficient.push_back(0);
                transmission_coefficient.push_back(0);
                absorption_coefficient.push_back(1);
            }
        }

        OBJECT_BASE_SURFACE(
            std::vector<float> &r,
            std::vector<float> &t,
            std::vector<float> &a)
        {
            reflexion_coefficient = r;
            transmission_coefficient = t;
            absorption_coefficient = a;
        }

        /** Destructor */
        ~OBJECT_BASE_SURFACE();
};

std::vector<int> multiply(std::vector<float>&, std::vector<int>&);