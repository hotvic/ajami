/*
 * This file is part of AJAMI.
 *
 * Copyright (C) 2014 Victor A. Santos <victoraur.santos@gmail.com>
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <gtk/gtk.h>


void on_in_trim_scale_value_changed         (GtkAdjustment   *adjustment,
                                             gpointer         user_data);
void on_comp_kn_1_value_changed             (GtkAdjustment   *adjustment,
                                             gpointer         user_data);
void on_comp_kn_2_value_changed             (GtkAdjustment   *adjustment,
                                             gpointer         user_data);
void on_comp_kn_3_value_changed             (GtkAdjustment   *adjustment,
                                             gpointer         user_data);
void on_lim_out_trim_scale_value_changed    (GtkAdjustment   *adjustment,
                                             gpointer         user_data);
void on_pan_scale_value_changed             (GtkAdjustment   *adjustment,
                                             gpointer         user_data);
void on_autoutton1_toggled                  (GtkToggleButton *togglebutton,
                                             gpointer         user_data);
void on_autoutton2_toggled                  (GtkToggleButton *togglebutton,
                                             gpointer         user_data);
void on_autoutton3_toggled                  (GtkToggleButton *togglebutton,
                                             gpointer         user_data);
void on_button11_clicked                    (GtkButton       *button,
                                             gpointer         user_data);
void on_button12_clicked                    (GtkButton       *button,
                                             gpointer         user_data);
void on_undo_button_clicked                 (GtkButton       *button,
                                             gpointer         user_data);
void on_lim_lh_scale_value_changed          (GtkAdjustment   *adjustment,
                                             gpointer         user_data);

void on_release_val_label_realize           (GtkWidget       *widget,
                                             gpointer         user_data);
gboolean on_low2mid_button_press_event      (GtkWidget       *widget,
                                             GdkEventButton  *event,
                                             gpointer         user_data);
gboolean on_low2mid_button_release_event    (GtkWidget       *widget,
                                             GdkEventButton  *event,
                                             gpointer         user_data);
gboolean on_mid2high_button_press_event     (GtkWidget       *widget,
                                             GdkEventButton  *event,
                                             gpointer         user_data);
gboolean on_mid2high_button_release_event   (GtkWidget       *widget,
                                             GdkEventButton  *event,
                                             gpointer         user_data);
void on_lim_input_hscale_value_changed      (GtkAdjustment   *adjustment,
                                             gpointer         user_data);
void on_lim_input_hscale_realize            (GtkWidget       *widget,
                                             gpointer         user_data);
void on_notebook1_realize                   (GtkWidget       *widget,
                                             gpointer         user_data);
void on_optionmenu1_realize                 (GtkWidget       *widget,
                                             gpointer         user_data);
void on_low_meter_lbl_realize               (GtkWidget       *widget,
                                             gpointer         user_data);
void on_mid_meter_lbl_realize               (GtkWidget       *widget,
                                             gpointer         user_data);
void on_autobutton_1_toggled                (GtkToggleButton *togglebutton,
                                             gpointer         user_data);
void on_autobutton_2_toggled                (GtkToggleButton *togglebutton,
                                             gpointer         user_data);
void on_autobutton_3_toggled                (GtkToggleButton *togglebutton,
                                             gpointer         user_data);
void on_boost_scale_value_changed           (GtkAdjustment   *adjustment,
                                             gpointer         user_data);
void on_setscene_activate                   (GtkMenuItem     *menuitem,
                                             gpointer         user_data);
void on_clearscene_activate                 (GtkMenuItem     *menuitem,
                                             gpointer         user_data);
void on_help_button_clicked                 (GtkButton       *button,
                                             gpointer         user_data);
void on_new_activate                        (GtkMenuItem     *menuitem,
                                             gpointer         user_data);
void on_open_activate                       (GtkMenuItem     *menuitem,
                                             gpointer         user_data);
void on_save_activate                       (GtkMenuItem     *menuitem,
                                             gpointer         user_data);
void on_save_as_activate                    (GtkMenuItem     *menuitem,
                                             gpointer         user_data);
void on_undo_activate                       (GtkMenuItem     *menuitem,
                                             gpointer         user_data);
void on_redo_activate                       (GtkMenuItem     *menuitem,
                                             gpointer         user_data);
void on_hscale_1_l_value_changed            (GtkAdjustment   *adjustment,
                                             gpointer         user_data);
void on_hscale_1_l_realize                  (GtkWidget       *widget,
                                             gpointer         user_data);
void on_hscale_1_m_value_changed            (GtkAdjustment   *adjustment,
                                             gpointer         user_data);
void on_hscale_1_m_realize                  (GtkWidget       *widget,
                                             gpointer         user_data);

void on_hscale_1_h_value_changed            (GtkAdjustment   *adjustment,
                                             gpointer         user_data);
void on_hscale_1_h_realize                  (GtkWidget       *widget,
                                             gpointer         user_data);
gboolean on_frame_l_enter_notify_event      (GtkWidget       *widget,
                                             GdkEventCrossing *event,
                                             gpointer         user_data);

gboolean
on_frame_m_enter_notify_event          (GtkWidget       *widget,
                                        GdkEventCrossing *event,
                                        gpointer         user_data);

gboolean
on_frame_h_enter_notify_event          (GtkWidget       *widget,
                                        GdkEventCrossing *event,
                                        gpointer         user_data);

void
on_help1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_keys1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_ports1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_in1_activate                        (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_left1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_right1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_out1_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_left2_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_right2_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_ports1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_in1_activate                        (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_left1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_right1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_out1_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_left2_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_right2_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_out_trim_scale_value_changed        (GtkAdjustment   *adjustment,
                                        gpointer         user_data);


void
on_jack_ports_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_about_prerequisites1_activate       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

gboolean scene_warning                 (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);
void on_low_active_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);
void on_low_mute_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);
void on_mid_active_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);
void on_mid_mute_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);
void on_high_active_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data);
void on_high_mute_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);
void on_hscale_1_l_value_changed       (GtkAdjustment   *adjustment,
                                        gpointer         user_data);
void on_hscale_1_l_realize             (GtkWidget       *widget,
                                        gpointer         user_data);
void on_hscale_1_m_value_changed       (GtkAdjustment   *adjustment,
                                        gpointer         user_data);
void on_hscale_1_m_realize             (GtkWidget       *widget,
                                        gpointer         user_data);
void on_hscale_1_h_value_changed       (GtkAdjustment   *adjustment,
                                        gpointer         user_data);
void on_hscale_1_h_realize             (GtkWidget       *widget,
                                        gpointer         user_data);
void on_low_bypass_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);
void on_mid_bypass_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);
void on_high_bypass_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data);
void on_solo_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);
void on_eq_bypass_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);
void on_limiter_bypass_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data);
void on_name_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data);
void on_scene_name_entry_changed       (GtkEditable     *editable,
                                        gpointer         user_data);
void on_scene_name_cancel_clicked      (GtkButton       *button,
                                        gpointer         user_data);
void on_scene_name_ok_clicked          (GtkButton       *button,
                                        gpointer         user_data);
void on_ft_bias_a_value_changed        (GtkAdjustment   *adjustment,
                                        gpointer         user_data);
void on_ft_bias_b_value_changed        (GtkAdjustment   *adjustment,
                                        gpointer         user_data);
void on_ft_rez_lp_a_value_changed      (GtkAdjustment   *adjustment,
                                        gpointer         user_data);
void on_ft_rez_hp_a_value_changed      (GtkAdjustment   *adjustment,
                                        gpointer         user_data);
void on_ft_rez_lp_b_value_changed      (GtkAdjustment   *adjustment,
                                        gpointer         user_data);
void on_ft_rez_hp_b_value_changed      (GtkAdjustment   *adjustment,
                                        gpointer         user_data);
void on_ft_bias_a_hp_value_changed     (GtkAdjustment   *adjustment,
                                        gpointer         user_data);
void on_ft_bias_b_hp_value_changed     (GtkAdjustment   *adjustment,
                                        gpointer         user_data);
void on_eqb_value_changed              (GtkAdjustment   *adjustment,
                                        gpointer         user_data);
void on_global_bypass_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);
void on_scene_menu_help_activate       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);
