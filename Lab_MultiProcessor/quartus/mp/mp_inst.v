	mp u0 (
		.clk_clk                           (<connected-to-clk_clk>),                           //                         clk.clk
		.new_sdram_controller_0_wire_addr  (<connected-to-new_sdram_controller_0_wire_addr>),  // new_sdram_controller_0_wire.addr
		.new_sdram_controller_0_wire_ba    (<connected-to-new_sdram_controller_0_wire_ba>),    //                            .ba
		.new_sdram_controller_0_wire_cas_n (<connected-to-new_sdram_controller_0_wire_cas_n>), //                            .cas_n
		.new_sdram_controller_0_wire_cke   (<connected-to-new_sdram_controller_0_wire_cke>),   //                            .cke
		.new_sdram_controller_0_wire_cs_n  (<connected-to-new_sdram_controller_0_wire_cs_n>),  //                            .cs_n
		.new_sdram_controller_0_wire_dq    (<connected-to-new_sdram_controller_0_wire_dq>),    //                            .dq
		.new_sdram_controller_0_wire_dqm   (<connected-to-new_sdram_controller_0_wire_dqm>),   //                            .dqm
		.new_sdram_controller_0_wire_ras_n (<connected-to-new_sdram_controller_0_wire_ras_n>), //                            .ras_n
		.new_sdram_controller_0_wire_we_n  (<connected-to-new_sdram_controller_0_wire_we_n>),  //                            .we_n
		.pio_0_external_connection_export  (<connected-to-pio_0_external_connection_export>),  //   pio_0_external_connection.export
		.pio_1_external_connection_export  (<connected-to-pio_1_external_connection_export>),  //   pio_1_external_connection.export
		.pio_2_external_connection_export  (<connected-to-pio_2_external_connection_export>),  //   pio_2_external_connection.export
		.pll_0_outclk2_clk                 (<connected-to-pll_0_outclk2_clk>),                 //               pll_0_outclk2.clk
		.reset_reset_n                     (<connected-to-reset_reset_n>),                     //                       reset.reset_n
		.uart_0_external_connection_rxd    (<connected-to-uart_0_external_connection_rxd>),    //  uart_0_external_connection.rxd
		.uart_0_external_connection_txd    (<connected-to-uart_0_external_connection_txd>)     //                            .txd
	);

