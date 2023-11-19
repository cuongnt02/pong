#include <SDL.h>
class Timer {
    public:
        Timer();

        void start();
        void stop();
        void pause();
        void unpause();
        Uint32 get_ticks();
        bool is_started();
        bool is_paused();

    private:
        Uint32 m_start_ticks;
        Uint32 m_paused_ticks;

        bool m_started;
        bool m_paused;
};
