#ifdef GL_ES
precision highp float;
#endif
uniform sampler2D from;
 uniform float animationKey;
 uniform bool reverse;
 vec2 resolution=vec2(640,480);
 float key;

// Adapted by Sergey Kosarevsky from:
// http://rectalogic.github.io/webvfx/examples_2transition-shader-pagecurl_8html-example.html

/*
Copyright (c) 2010 Hewlett-Packard Development Company, L.P. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above
     copyright notice, this list of conditions and the following disclaimer
     in the documentation and/or other materials provided with the
     distribution.
   * Neither the name of Hewlett-Packard nor the names of its
     contributors may be used to endorse or promote products derived from
     this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
in vec2 texCoord;
*/

const float MIN_AMOUNT = -0.16;
const float MAX_AMOUNT = 1.3;


const float PI = 3.141592653589793;

const float scale = 512.0;
const float sharpness = 3.0;
float amount = key* (MAX_AMOUNT - MIN_AMOUNT) + MIN_AMOUNT;
float cylinderCenter = amount;
float cylinderAngle = 2.0 * PI * amount;
// 360 degrees * amount


const float cylinderRadius = 1.0 / PI / 2.0;

vec3 hitPoint(float hitAngle, float yc, vec3 point, mat3 rrotation)
{
        float hitPoint = hitAngle / (2.0 * PI);
        point.y = hitPoint;
        return rrotation * point;
}

vec4 antiAlias(vec4 color1, vec4 color2, float distanc)
{
        distanc *= scale;
        if (distanc < 0.0) return color2;
        if (distanc > 2.0) return color1;
        float dd = pow(1.0 - distanc / 2.0, sharpness);
        return ((color2 - color1) * dd) + color1;
}

float distanceToEdge(vec3 point)
{
        float dx = abs(point.x > 0.5 ? 1.0 - point.x : point.x);
        float dy = abs(point.y > 0.5 ? 1.0 - point.y : point.y);
        if (point.x < 0.0) dx = -point.x;
        if (point.x > 1.0) dx = point.x - 1.0;
        if (point.y < 0.0) dy = -point.y;
        if (point.y > 1.0) dy = point.y - 1.0;
        if ((point.x < 0.0 || point.x > 1.0) && (point.y < 0.0 || point.y > 1.0)) return sqrt(dx * dx + dy * dy);
        return min(dx, dy);
}

vec4 seeThrough(float yc, vec2 p, mat3 rotation, mat3 rrotation)
{
        float hitAngle = PI - (acos(yc / cylinderRadius) - cylinderAngle);
        vec3 point = hitPoint(hitAngle, yc, rotation * vec3(p, 1.0), rrotation);
        if (yc <= 0.0 && (point.x < 0.0 || point.y < 0.0 || point.x > 1.0 || point.y > 1.0))
        {
          vec2 texCoord = gl_FragCoord.xy / resolution.xy;
                return vec4(0,0,0,0);
        }

        if (yc > 0.0) return texture2D(from, p);

        vec4 color = texture2D(from, point.xy);
        vec4 tcolor = vec4(0.0);

        return antiAlias(color, tcolor, distanceToEdge(point));
}

vec4 seeThroughWithShadow(float yc, vec2 p, vec3 point, mat3 rotation, mat3 rrotation)
{
        float shadow = distanceToEdge(point) * 30.0;
        shadow = (1.0 - shadow) / 3.0;

        if (shadow < 0.0) shadow = 0.0; else shadow *= amount;

        vec4 shadowColor = seeThrough(yc, p, rotation, rrotation);
        shadowColor.r -= shadow;
        shadowColor.g -= shadow;
        shadowColor.b -= shadow;

        return shadowColor;
}

vec4 backside(float yc, vec3 point)
{
        vec4 color = texture2D(from, point.xy);
        float gray = (color.r + color.b + color.g) / 15.0;
        gray += (8.0 / 10.0) * (pow(1.0 - abs(yc / cylinderRadius), 2.0 / 10.0) / 2.0 + (5.0 / 10.0));
        color.rgb = vec3(gray);
        return color;
}

vec4 behindSurface(float yc, vec3 point, mat3 rrotation)
{
        float shado = (1.0 - ((-cylinderRadius - yc) / amount * 7.0)) / 6.0;
        shado *= 1.0 - abs(point.x - 0.5);

        yc = (-cylinderRadius - cylinderRadius - yc);

        float hitAngle = (acos(yc / cylinderRadius) + cylinderAngle) - PI;
        point = hitPoint(hitAngle, yc, point, rrotation);

        if (yc < 0.0 && point.x >= 0.0 && point.y >= 0.0 && point.x <= 1.0 && point.y <= 1.0 && (hitAngle < PI || amount > 0.5))
        {
                shado = 1.0 - (sqrt(pow(point.x - 0.5, 2.0) + pow(point.y - 0.5, 2.0)) / (71.0 / 100.0));
                shado *= pow(-yc / cylinderRadius, 3.0);
                shado *= 0.5;
        }
        else
        {
                shado = 0.0;
        }

        vec2 texCoord = gl_FragCoord.xy / resolution.xy;
        vec4 bground =vec4(0,0,0,0);
        return vec4(bground.rgb - shado, bground.a);
}

void main()
{

    if (reverse)key=1.0-animationKey;
    else key=animationKey;
    amount = key* (MAX_AMOUNT - MIN_AMOUNT) + MIN_AMOUNT;
    cylinderCenter = amount;
    cylinderAngle = 2.0 * PI * amount;
  vec2 texCoord = gl_FragCoord.xy / resolution.xy;

  const float angle = 30.0 * PI / 180.0;
        float c = cos(-angle);
        float s = sin(-angle);

        mat3 rotation = mat3( c, s, 0,
                                                                -s, c, 0,
                                                                0.12, 0.258, 1
                                                                );
        c = cos(angle);
        s = sin(angle);

        mat3 rrotation = mat3(	c, s, 0,
                                                                        -s, c, 0,
                                                                        0.15, -0.5, 1
                                                                );

        vec3 point = rotation * vec3(texCoord, 1.0);

        float yc = point.y - cylinderCenter;

        if (yc < -cylinderRadius)
        {
                // Behind surface
                gl_FragColor = behindSurface(yc, point, rrotation);
                return;
        }

        if (yc > cylinderRadius)
        {
                // Flat surface
                gl_FragColor = texture2D(from, texCoord);
                return;
        }

        float hitAngle = (acos(yc / cylinderRadius) + cylinderAngle) - PI;

        float hitAngleMod = mod(hitAngle, 2.0 * PI);
        if ((hitAngleMod > PI && amount < 0.5) || (hitAngleMod > PI/2.0 && amount < 0.0))
        {
                gl_FragColor = seeThrough(yc, texCoord, rotation, rrotation);
                return;
        }

        point = hitPoint(hitAngle, yc, point, rrotation);

        if (point.x < 0.0 || point.y < 0.0 || point.x > 1.0 || point.y > 1.0)
        {
                gl_FragColor = seeThroughWithShadow(yc, texCoord, point, rotation, rrotation);
                return;
        }

        vec4 color = backside(yc, point);

        vec4 otherColor;
        if (yc < 0.0)
        {
                float shado = 1.0 - (sqrt(pow(point.x - 0.5, 2.0) + pow(point.y - 0.5, 2.0)) / 0.71);
                shado *= pow(-yc / cylinderRadius, 3.0);
                shado *= 0.5;
                otherColor = vec4(0.0, 0.0, 0.0, shado);
        }
        else
        {
                otherColor = texture2D(from, texCoord);
        }

        color = antiAlias(color, otherColor, cylinderRadius - abs(yc));

        vec4 cl = seeThroughWithShadow(yc, texCoord, point, rotation, rrotation);
        float dist = distanceToEdge(point);

        gl_FragColor = antiAlias(color, cl, dist);
}
