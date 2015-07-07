MRuby::Gem::Specification.new('mruby-sdl2_image') do |spec|
  spec.license = 'MIT'
  spec.authors = 'moon4u'
  spec.add_dependency('mruby-sdl2')
  spec.cc.flags << '`sdl2-config --cflags`'
  spec.linker.flags_before_libraries << '`sdl2-config --libs`'
end
