#include "text.h"
#include "globals.h"
#include "log.h"

int Text::render() const {

    if (!font_texture.load_from_redered_text(m_content, m_color)) {
        log_print("ERROR: Load text to texture failed!");
        return 0;
    }

    font_texture.render(m_x, m_y);
    return 1;
}
