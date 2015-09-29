#include "sdl2_image.h"
#include "mruby/value.h"
#include "mruby/string.h"
#include "sdl2_surface.h"
#include "sdl2_render.h"
#include "sdl2_rwops.h"
#include <SDL2/SDL_image.h>

static mrb_value
mrb_sdl2_surface_image_load(mrb_state *mrb, mrb_value self)
{
  SDL_Surface *result;
  mrb_value file;
  mrb_get_args(mrb, "S", &file);
  result = IMG_Load(RSTRING_PTR(file));
  return mrb_sdl2_video_surface(mrb, result, true);
}

static mrb_value
mrb_sdl2_surface_image_load_rw(mrb_state *mrb, mrb_value self)
{
  SDL_Surface *result;
  mrb_value src;
  mrb_bool freesrc_mr;
  SDL_RWops * rwops;
  int freesrc;
  int argc = mrb_get_args(mrb, "o|b", &src, &freesrc_mr);
  if (argc == 1) {
    freesrc = 1;
  } else {
    freesrc = (freesrc_mr == MRB_TT_FLOAT) ? 0 : 1;
  }
  rwops = mrb_sdl2_rwops_get_ptr(mrb, src);
  result = IMG_Load_RW(rwops, freesrc);

  return mrb_sdl2_video_surface(mrb, result, true);
}

static mrb_value
mrb_sdl2_image_renderer_load(mrb_state *mrb, mrb_value self)
{
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  mrb_value file;
  mrb_get_args(mrb, "S", &file);
  renderer = mrb_sdl2_video_renderer_get_ptr(mrb, self);
  texture = IMG_LoadTexture(renderer, RSTRING_PTR(file));
  if (texture == NULL)
    mruby_sdl2_raise_error(mrb);
    
  return mrb_sdl2_video_texture(mrb, texture);
}

static mrb_value
mrb_sdl2_image_renderer_load_rw(mrb_state *mrb, mrb_value self)
{
  SDL_Renderer *renderer;
  mrb_value src;
  mrb_bool freesrc_mr;
  SDL_RWops * rwops;
  int freesrc;
  int argc = mrb_get_args(mrb, "o|b", &src, &freesrc_mr);
  renderer = mrb_sdl2_video_renderer_get_ptr(mrb, self);
  if (argc == 1) {
    freesrc = 1;
  } else {
    freesrc = (freesrc_mr == MRB_TT_FLOAT) ? 0 : 1;
  }
  rwops = mrb_sdl2_rwops_get_ptr(mrb, src);
  return mrb_sdl2_video_texture(mrb, IMG_LoadTexture_RW(renderer, rwops, freesrc));
}

static mrb_value mrb_sdl2_image_isICO (mrb_state *mrb, mrb_value self) { return (IMG_isICO (mrb_sdl2_rwops_get_ptr(mrb, self)) == 0) ? mrb_false_value() : mrb_true_value(); }
static mrb_value mrb_sdl2_image_isCUR (mrb_state *mrb, mrb_value self) { return (IMG_isCUR (mrb_sdl2_rwops_get_ptr(mrb, self)) == 0) ? mrb_false_value() : mrb_true_value(); }
static mrb_value mrb_sdl2_image_isBMP (mrb_state *mrb, mrb_value self) { return (IMG_isBMP (mrb_sdl2_rwops_get_ptr(mrb, self)) == 0) ? mrb_false_value() : mrb_true_value(); }
static mrb_value mrb_sdl2_image_isGIF (mrb_state *mrb, mrb_value self) { return (IMG_isGIF (mrb_sdl2_rwops_get_ptr(mrb, self)) == 0) ? mrb_false_value() : mrb_true_value(); }
static mrb_value mrb_sdl2_image_isJPG (mrb_state *mrb, mrb_value self) { return (IMG_isJPG (mrb_sdl2_rwops_get_ptr(mrb, self)) == 0) ? mrb_false_value() : mrb_true_value(); }
static mrb_value mrb_sdl2_image_isLBM (mrb_state *mrb, mrb_value self) { return (IMG_isLBM (mrb_sdl2_rwops_get_ptr(mrb, self)) == 0) ? mrb_false_value() : mrb_true_value(); }
static mrb_value mrb_sdl2_image_isPCX (mrb_state *mrb, mrb_value self) { return (IMG_isPCX (mrb_sdl2_rwops_get_ptr(mrb, self)) == 0) ? mrb_false_value() : mrb_true_value(); }
static mrb_value mrb_sdl2_image_isPNG (mrb_state *mrb, mrb_value self) { return (IMG_isPNG (mrb_sdl2_rwops_get_ptr(mrb, self)) == 0) ? mrb_false_value() : mrb_true_value(); }
static mrb_value mrb_sdl2_image_isPNM (mrb_state *mrb, mrb_value self) { return (IMG_isPNM (mrb_sdl2_rwops_get_ptr(mrb, self)) == 0) ? mrb_false_value() : mrb_true_value(); }
static mrb_value mrb_sdl2_image_isTIF (mrb_state *mrb, mrb_value self) { return (IMG_isTIF (mrb_sdl2_rwops_get_ptr(mrb, self)) == 0) ? mrb_false_value() : mrb_true_value(); }
static mrb_value mrb_sdl2_image_isXCF (mrb_state *mrb, mrb_value self) { return (IMG_isXCF (mrb_sdl2_rwops_get_ptr(mrb, self)) == 0) ? mrb_false_value() : mrb_true_value(); }
static mrb_value mrb_sdl2_image_isXPM (mrb_state *mrb, mrb_value self) { return (IMG_isXPM (mrb_sdl2_rwops_get_ptr(mrb, self)) == 0) ? mrb_false_value() : mrb_true_value(); }
static mrb_value mrb_sdl2_image_isXV  (mrb_state *mrb, mrb_value self) { return (IMG_isXV  (mrb_sdl2_rwops_get_ptr(mrb, self)) == 0) ? mrb_false_value() : mrb_true_value(); }
static mrb_value mrb_sdl2_image_isWEBP(mrb_state *mrb, mrb_value self) { return (IMG_isWEBP(mrb_sdl2_rwops_get_ptr(mrb, self)) == 0) ? mrb_false_value() : mrb_true_value(); }

static mrb_value
mrb_sdl2_surface_image_init(mrb_state *mrb, mrb_value self) {
  mrb_int flags;
  mrb_get_args(mrb, "i", &flags);
  
  return mrb_fixnum_value(IMG_Init(flags));
}

void mrb_mruby_sdl2_image_gem_init(mrb_state *mrb) {
  int arena_size;
  struct RClass *class_Surface;
  struct RClass *class_Renderer;
  struct RClass *mod_Video;
  struct RClass *class_RWops;
  struct RClass *mod_Image;
  
  mod_Video      = mrb_module_get_under   (mrb, mod_SDL2,  "Video");
  class_Renderer = mrb_class_get_under    (mrb, mod_Video, "Renderer");
  class_Surface  = mrb_class_get_under    (mrb, mod_Video, "Surface");
  class_RWops    = mrb_class_get_under    (mrb, mod_SDL2,  "RWops");
  mod_Image      = mrb_define_module_under(mrb, mod_SDL2,  "Image");
  
  mrb_define_module_function(mrb, mod_Image, "init", mrb_sdl2_surface_image_init, MRB_ARGS_REQ(1));
  
  mrb_define_class_method(mrb, class_Surface, "load",    mrb_sdl2_surface_image_load,    MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, class_Surface, "load_RW", mrb_sdl2_surface_image_load_rw, MRB_ARGS_REQ(1) | MRB_ARGS_REQ(2));

  mrb_define_method(mrb, class_Renderer, "load",    mrb_sdl2_image_renderer_load,    MRB_ARGS_REQ(1));
  mrb_define_method(mrb, class_Renderer, "load_rw", mrb_sdl2_image_renderer_load_rw, MRB_ARGS_REQ(1) | MRB_ARGS_REQ(2));

  mrb_define_method(mrb, class_RWops, "is_ICO?",  mrb_sdl2_image_isICO,  MRB_ARGS_NONE());
  mrb_define_method(mrb, class_RWops, "is_CUR?",  mrb_sdl2_image_isCUR,  MRB_ARGS_NONE());
  mrb_define_method(mrb, class_RWops, "is_BMP?",  mrb_sdl2_image_isBMP,  MRB_ARGS_NONE());
  mrb_define_method(mrb, class_RWops, "is_GIF?",  mrb_sdl2_image_isGIF,  MRB_ARGS_NONE());
  mrb_define_method(mrb, class_RWops, "is_JPG?",  mrb_sdl2_image_isJPG,  MRB_ARGS_NONE());
  mrb_define_method(mrb, class_RWops, "is_LBM?",  mrb_sdl2_image_isLBM,  MRB_ARGS_NONE());
  mrb_define_method(mrb, class_RWops, "is_PCX?",  mrb_sdl2_image_isPCX,  MRB_ARGS_NONE());
  mrb_define_method(mrb, class_RWops, "is_PNG?",  mrb_sdl2_image_isPNG,  MRB_ARGS_NONE());
  mrb_define_method(mrb, class_RWops, "is_PNM?",  mrb_sdl2_image_isPNM,  MRB_ARGS_NONE());
  mrb_define_method(mrb, class_RWops, "is_TIF?",  mrb_sdl2_image_isTIF,  MRB_ARGS_NONE());
  mrb_define_method(mrb, class_RWops, "is_XCF?",  mrb_sdl2_image_isXCF,  MRB_ARGS_NONE());
  mrb_define_method(mrb, class_RWops, "is_XPM?",  mrb_sdl2_image_isXPM,  MRB_ARGS_NONE());
  mrb_define_method(mrb, class_RWops, "is_XV?",   mrb_sdl2_image_isXV,   MRB_ARGS_NONE());
  mrb_define_method(mrb, class_RWops, "is_WEBP?", mrb_sdl2_image_isWEBP, MRB_ARGS_NONE());

  arena_size = mrb_gc_arena_save(mrb);

  /* IMG_InitFlags */
  mrb_define_const(mrb, mod_Image, "IMG_INIT_JPG",      mrb_fixnum_value(IMG_INIT_JPG));
  mrb_define_const(mrb, mod_Image, "IMG_INIT_PNG",      mrb_fixnum_value(IMG_INIT_PNG));
  mrb_define_const(mrb, mod_Image, "IMG_INIT_TIF",      mrb_fixnum_value(IMG_INIT_TIF));
  mrb_define_const(mrb, mod_Image, "IMG_INIT_WEBP",     mrb_fixnum_value(IMG_INIT_WEBP));

  mrb_gc_arena_restore(mrb, arena_size);

}

void mrb_mruby_sdl2_image_gem_final(mrb_state *mrb) {

}
