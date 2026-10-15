import streamlit as st
import subprocess
import os

st.set_page_config(page_title="Codificador 5G/6G - LZW", layout="centered")

st.title("📡 Sistema de Codificación 5G/6G")
st.markdown("Sube un archivo para analizar su entropía, comprimirlo usando LZW y verificar su reconstrucción.")

# 1. Controles de la Interfaz
archivo_subido = st.file_uploader("Selecciona un archivo multimedia o de texto")
n_bits = st.selectbox("Tamaño de bloque (N bits)", [8, 64, 128, 512, 1024, 2048, 4096, 8192])

if st.button("Procesar Archivo"):
    if archivo_subido is not None:
        # Asegurar que exista la carpeta data/
        os.makedirs("data", exist_ok=True)
        ruta_guardado = os.path.join("data", archivo_subido.name)
        
        with open(ruta_guardado, "wb") as f:
            f.write(archivo_subido.getbuffer())
        
        st.info(f"Procesando {archivo_subido.name} con bloques de {n_bits} bits...")

        # 2. Conectar la Interfaz con el código C++ de forma segura
        ruta_ejecutable = os.path.join(os.getcwd(), "codificador_6g.exe")

        # Validar si el archivo ejecutable realmente existe antes de correrlo
        if not os.path.exists(ruta_ejecutable):
            st.error(f"No se encontró el archivo ejecutable en: {ruta_ejecutable}. Asegúrate de compilarlo primero en la terminal.")
        else:
            comando = [ruta_ejecutable, ruta_guardado, str(n_bits)]
            
            # Ejecutamos con text=False para capturar los bytes en crudo y evitar problemas con la cp1252 de Windows
            resultado = subprocess.run(comando, capture_output=True, text=False)

            # Decodificamos de forma segura ignorando caracteres binarios conflictivos
            stdout_texto = resultado.stdout.decode('utf-8', errors='ignore') if resultado.stdout else ""
            stderr_texto = resultado.stderr.decode('utf-8', errors='ignore') if resultado.stderr else ""

            # 3. Mostrar los resultados de forma segura
            if resultado.returncode == 0:
                st.success("¡Procesamiento y compresión exitosos!")
                
                # Organizar la salida visualmente en pestañas
                tab1, tab2 = st.tabs(["📊 Métricas y Resumen", "🔍 Traza Paso a Paso (LZW)"])
                
                with tab1:
                    st.subheader("Métricas de Shannon y Consola General")
                    st.text_area("Salida completa del núcleo C++", stdout_texto, height=250)
                
                with tab2:
                    st.subheader("Proceso iterativo del diccionario LZW")
                    st.markdown("Registro paso a paso de cómo el compresor detectó patrones y generó códigos dinámicos:")
                    
                    if stdout_texto:
                        lineas_consola = stdout_texto.split("\n")
                        pasos_lzw = [linea for linea in lineas_consola if "[LZW Paso]" in linea]
                        
                        if pasos_lzw:
                            st.code("\n".join(pasos_lzw), language="text")
                        else:
                            st.info("No se encontraron registros '[LZW Paso]'. Asegúrate de haber vuelto a compilar tu código en C++.")
                    else:
                        st.warning("El núcleo de C++ no devolvió ninguna salida estándar.")
                
                # 4. Botones de descarga
                st.markdown("---")
                st.subheader("Archivos de Salida")
                col1, col2 = st.columns(2)
                
                if os.path.exists("data/comprimido.bin"):
                    with open("data/comprimido.bin", "rb") as file_comp:
                        col1.download_button("📥 Descargar Comprimido (.bin)", file_comp, file_name="comprimido.bin")
                
                if os.path.exists("data/reconstruido.bin"):
                    with open("data/reconstruido.bin", "rb") as file_rec:
                        col2.download_button("🔄 Descargar Reconstruido", file_rec, file_name=f"reconstruido_{archivo_subido.name}")
            else:
                st.error("Ocurrió un error en el núcleo de C++.")
                st.error(stderr_texto if stderr_texto else "Error desconocido sin mensaje de error estándar.")
    else:
        st.warning("Por favor, sube un archivo primero.")