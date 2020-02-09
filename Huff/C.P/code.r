graf<-read.table("~/Downloads/Huffman-master/Huff da ju (com o menu)/c.p/fila_com_e_sem_heap", header = TRUE, sep = " ")
plot(graf$without_heap~graf$value, main="Fila com heap X Fila sem heap", xlab="Valores", ylab="Comparações", col="blue")
points(graf$with_heap~graf$value, col="red")