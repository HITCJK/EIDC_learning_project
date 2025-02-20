typedef struct voltage_list_
{
    struct voltage_list_ *next;
    int voltage_count_output;
    int voltage_count_display;
}voltage_list;
int get_unit_of_time(int cycle);
voltage_list *create_voltage_list_sine_wave(int cycle, float Vpp, int unit_of_time);
voltage_list *create_voltage_list_triangle_wave(int cycle, float Vpp, int unit_of_time);
voltage_list *create_voltage_list_square_wave(int cycle, float Vpp, int unit_of_time);
voltage_list *create_voltage_list_DC_wave(int cycle, float Vpp, int unit_of_time);
void free_voltage_list(voltage_list *head);