   M S B A M L   `   `   `  ����I  EarduinoControl, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null/clr-namespace:arduinoControlarduinoControl  5   	       arduinoControl.MainWindow   5   	   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   .localclr-namespace:arduinoControl     5   	     � Title$  
MainWindow��5   	   $	��450��6   $	��800��6)   .��5	      � .+�5
   
   �� $��Подключение��6   $
��Left=�6&   $��
176,26,0,0q�6A   $	��Top=�6U   $��47��6m   $	��157��6y   �� 5   
   -   5        $��cBSelectPorts��5   �   $
��Left=�6   $��350,104,0,0q�6.   $	��Top=�6C   $	��126��6[   $��28��6g   6�   �� 5   
   $��COM Port��6   $
��Left=�6#   $��
345,76,0,0q�6>   $	��Top=�6R    J� RenderTransformOrigin$ 0.5,0.5&�6j   z�5      V� 5      .~�5      �� �� 5       �� AngleX$ 2.023Q�6$   �� 5      T� 5       T� X$ 0.459Q�6)   5      5      �� 5   
   -   5        $��btnUpdatePorts��5   �   $4��.Обновить список COM портов��6   $
��Left=�66   $��
27,104,0,0q�6Q   $	��Top=�6e   $	��271��6}   $��28��6�   6�   �� 5   
   -   5        $��
btnConnect��5   �   $��Подключить��6   $
��Left=�6&   $��119,170,0,0q�6A   $	��Top=�6V   $��75��6n   6�   �� 5   
   -   5        $��btnDisconnect��5   x   $��Отключить��6   $
��Left=�6%   $��386,170,0,0q�6@   $	��Top=�6U   $��75��6m   6�   A� 5   
   -   5        $��state��5      ���	#FFF4F4F5$
��Left=�60   $��35��6K   $��273,170,0,0q�6W   
���   �$	��Top=�6{   $��35��6�   $ 0.454,0.164&�6�   �� 5   
   -   5        $��btnLedOn��5   v   $��
Вкл LED��6   $
��Left=�6#   $��119,279,0,0q�6>   $	��Top=�6S   $��75��6k   6�   �� 5   
   -   5        $��	btnLedOff��5   w   $��Выкл LED��6   $
��Left=�6$   $��386,279,0,0q�6?   $	��Top=�6T   $��75��6l   6�   5      5      