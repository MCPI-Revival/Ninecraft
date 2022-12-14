#include <string.h>

unsigned char main_fsh[] = (
    "#version 100\n"
    "precision mediump float;\n"
    "// Texture\n"
    "uniform bool u_has_texture;\n"
    "uniform sampler2D u_texture_unit;\n"
    "// Color\n"
    "varying vec4 v_color;\n"
    "varying vec4 v_texture_pos;\n"
    "// Alpha Test\n"
    "uniform bool u_alpha_test;\n"
    "// Fog\n"
    "uniform bool u_fog;\n"
    "uniform vec4 u_fog_color;\n"
    "uniform bool u_fog_is_linear;\n"
    "uniform float u_fog_start;\n"
    "uniform float u_fog_end;\n"
    "varying vec4 v_fog_eye_position;\n"
    "// Main\n"
    "void main(void) {\n"
    "    gl_FragColor = v_color;\n"
    "    // Texture\n"
    "    if (u_has_texture) {\n"
    "        gl_FragColor *= texture2D(u_texture_unit, v_texture_pos.xy);\n"
    "    }\n"
    "    // Alpha Test\n"
    "    if (u_alpha_test && gl_FragColor.a <= 0.1) {\n"
    "        discard;\n"
    "    }\n"
    "    // Fog\n"
    "    if (u_fog) {\n"
    "        float fog_factor;\n"
    "        if (u_fog_is_linear) {\n"
    "            fog_factor = (u_fog_end - length(v_fog_eye_position)) / (u_fog_end - u_fog_start);\n"
    "        } else {\n"
    "            fog_factor = exp(-u_fog_start * length(v_fog_eye_position));\n"
    "        }\n"
    "        gl_FragColor = mix(gl_FragColor, u_fog_color, 1.0 - clamp(fog_factor, 0.0, 1.0));\n"
    "    }\n"
    "}\n"
);

size_t main_fsh_len = sizeof(main_fsh);

unsigned char main_vsh[] = (
    "#version 100\n"
    "precision mediump float;\n"
    "// Matrices\n"
    "uniform mat4 u_projection;\n"
    "uniform mat4 u_model_view;\n"
    "uniform mat4 u_texture;\n"
    "// Texture\n"
    "attribute vec3 a_vertex_coords;\n"
    "attribute vec2 a_texture_coords;\n"
    "varying vec4 v_texture_pos;\n"
    "// Color\n"
    "attribute vec4 a_color;\n"
    "varying vec4 v_color;\n"
    "// Fog\n"
    "varying vec4 v_fog_eye_position;\n"
    "// Main\n"
    "void main(void) {\n"
    "    v_texture_pos = u_texture * vec4(a_texture_coords.xy, 0.0, 1.0);\n"
    "    gl_Position = u_projection * u_model_view * vec4(a_vertex_coords.xyz, 1.0);\n"
    "    v_color = a_color;\n"
    "    v_fog_eye_position = u_model_view * vec4(a_vertex_coords.xyz, 1.0);\n"
    "}\n"
);

size_t main_vsh_len = sizeof(main_vsh);