option (GETTEXT_BINARIES_DIR
        "If gettext binaries are in a undefault directory define this here")

if (GETTEXT_BINARIES_DIR)
    set (GettextTranslate_BINARIES ${GETTEXT_BINARIES_DIR})
endif (GETTEXT_BINARIES_DIR)

set (GettextTranslate_GMO_BINARY ON)

# Call GettextTranslate macro from GettextTranslate module
GettextTranslate()
