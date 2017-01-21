//
// Copyright (c) 2017 ZhuYaDong aeix@foxmail.com
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//

#include "nanovg_css.h"

static float maxf(float a, float b) { return a > b ? a : b; }
static float minf(float a, float b) { return a < b ? a : b; }

void nvcssBoxShadow(NVGcontext *vg,
                    float x, float y, float w, float h,
                    float l1, float l2, float l3, float l4,
                    NVGcolor color, int inset)
{
  NVGpaint shadowPaint;
  NVGcolor icol, ocol;
  float sx = x+l1-l4*0.5f;
  float sy = y+l2-l4*0.5f;
  float sw = w+l4;
  float sh = h+l4;

  if (inset)
    icol = nvgRGBA(0,0,0,0), ocol=color;
  else
    icol = color, ocol=nvgRGBA(0,0,0,0);
  shadowPaint = nvgBoxGradient(vg, sx,sy,sw,sh, 4, l3, icol, ocol);

  nvgBeginPath(vg);
  if (inset)
    nvgRect(vg, x,y,w,h);
  else {
    nvgRect(vg, minf(x, sx-l3*0.5f),minf(y, sy-l3*0.5f),sw+l3,sh+l3);
    nvgRect(vg, x,y,w,h);
    nvgPathWinding(vg, NVG_HOLE);
  }
  nvgFillPaint(vg, shadowPaint);
  nvgFill(vg);
}
