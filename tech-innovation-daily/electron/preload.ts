import { contextBridge, ipcRenderer } from "electron";

contextBridge.exposeInMainWorld("newsDesk", {
  getDigest: () => ipcRenderer.invoke("news:getDigest")
});
