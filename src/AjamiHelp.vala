using Gtk;


namespace Ajami {
    private MessageDialog msg_dialog = null;

    public void message(Gtk.MessageType type, string message) {
        if (msg_dialog != null) msg_dialog.destroy();

        msg_dialog = new MessageDialog(main_window,
                                       DialogFlags.DESTROY_WITH_PARENT,
                                       type, Gtk.ButtonsType.CLOSE,
                                       "%s", message);

        msg_dialog.response.connect((resonse_id) => { msg_dialog.destroy(); });
        msg_dialog.show();
    }
}
