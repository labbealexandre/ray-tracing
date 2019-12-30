class OBJECT_BASE_SURFACE {
    private:
        float reflexion_coefficient;
        float transmission_coefficient;

    public:

        /** Constructors */
        OBJECT_BASE_SURFACE() {
            reflexion_coefficient = 1;
            transmission_coefficient = 1;
        }

        OBJECT_BASE_SURFACE(float r, float t) {
            reflexion_coefficient = r;
            transmission_coefficient = t;
        }

        /** Destructor */
        ~OBJECT_BASE_SURFACE();

};