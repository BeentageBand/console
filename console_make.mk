define $(_flavor_)_$(_feat_)_MAKE
$(_flavor_)_$(_feat_)_inc=arg_parser.h console.h console_composite.h
$(_flavor_)_$(_feat_)_lib_objs=arg_parser console console_composite
$(_flavor_)_$(_feat_)_lib=console
endef

-include $(PROJ_MAK_DIR)/epilog.mk