ifdef DEFINE_INIT_VALUE
    VALUE = "Hello!"
endif

ifeq ($(CMD),colon)
    VALUE := “Hello all the World!”
endif

ifeq ($(CMD),question_mark)
    VALUE ?= “Hello World!”
endif

ifeq ($(CMD),plus)
    VALUE += “Danny!”
endif



all:
    @echo $(VALUE)