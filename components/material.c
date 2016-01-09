#include <string.h>
#include "../components/enum.h"
#include "material.h"

/* Size returns the size of the Material component */
static size_t Size()
{
  return sizeof(struct Material);
}

/* NewMaterial creates a new material component from the given shader sources */
struct Material * NewMaterial(const char *fs, const char *vs, const char *gs)
{
  GLint compiled, linked;
  struct Material *m;
  struct tv_Component *c;

  m = malloc(sizeof(struct Material));
  c = (struct tv_Component*)m;
  c->id = COMPONENT_MESH;
  c->Size = Size;

  m->fs = 0;
  m->vs = 0;
  m->gs = 0;

  /* create shader program */
  if(m->program == 0){
    GLint len;

    /* vertex shader */
    m->vs = glCreateShader(GL_VERTEX_SHADER);
    len = strlen(vs);
    glShaderSource(m->vs, 1, &vs, &len);
    glCompileShader(m->vs);
    glGetShaderiv(m->vs, GL_COMPILE_STATUS, &compiled);
    if(compiled == GL_FALSE){
      GLint logSz;
      GLchar *log;

      glGetShaderiv(m->vs, GL_INFO_LOG_LENGTH, &logSz);
      log = malloc(logSz * sizeof(GLchar));
      glGetShaderInfoLog(m->vs, logSz, &logSz, log);
      puts("error: vertex shader compilation failed");
      puts(log);
      free(log);
    }
    /* fragment shader */
    m->fs = glCreateShader(GL_FRAGMENT_SHADER);
    len = strlen(fs);
    glShaderSource(m->fs, 1, &fs, &len);
    glCompileShader(m->fs);
    glGetShaderiv(m->fs, GL_COMPILE_STATUS, &compiled);
    if(compiled == GL_FALSE){
      GLint logSz;
      GLchar *log;

      glGetShaderiv(m->fs, GL_INFO_LOG_LENGTH, &logSz);
      log = malloc(logSz * sizeof(GLchar));
      glGetShaderInfoLog(m->fs, logSz, &logSz, log);
      puts("error: fragment shader compilation failed");
      puts(log);
      free(log);
    }

    /* link shaders */
    m->program = glCreateProgram();
    glAttachShader(m->program, m->vs);
    glAttachShader(m->program, m->fs);
    glLinkProgram(m->program);
    glGetProgramiv(m->program, GL_LINK_STATUS, &linked);
    if(linked == GL_FALSE){
      GLint logSz;
      GLchar *log;

      glGetProgramiv(m->program, GL_INFO_LOG_LENGTH, &logSz);
      log = malloc(logSz * sizeof(GLchar));
      glGetProgramInfoLog(m->program, logSz, &logSz, log);
      puts(log);
      free(log);
    }
    /* get the uniforms */
    m->mvp = glGetUniformLocation(m->program, "mvp");
  }
  return m;
}

