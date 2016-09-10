using Gtk;

namespace Ajami
{
    public class Stereo
    {
        public Stereo()
        {
            for (int i = 0; i < 3; i++)
            {
                _state.set_callback(StateFlags.STEREO_WIDTH(i), value_changed);
                CAjami.Process.set_stereo_width(i, 0.0f);


                /*  This is a holdover from when we had per band balance.  It is still
                    needed until Steve gets a chance to clean up the stereo balance hacks
                    that I've done.  JCD  */

                CAjami.Process.set_stereo_balance(i, 0.0f);
            }
        }
    }

    public static void value_changed(int id, double val)
    {
        CAjami.Process.set_stereo_width(id - StateFlags.STEREO_WIDTH(0), val);
    }
}